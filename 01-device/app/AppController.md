# AppController

[← Application 模块](README.md)

## 1. 定位

`AppController` 是应用流程协调器，回答：

> 一个用户事件或 Service 事件发生后，LongPet 下一步应该做什么？

它是 UI、状态机和 Service 的“编排层”，但不实现具体算法。

## 2. 输入事件

来自 UI：

```text
controlRequested
talkRequested
careRequested
reminderRequested
reminderAcknowledgeRequested
reminderCompleteRequested
settingsRequested
userConfirmedSafe
wakeRequested
```

来自 Service：

```text
keywordDetected
humanPresenceChanged
gestureRecognized
speechSessionStateChanged
asrFinal
replyReady
playbackFinished
reminderTriggered / reminderPresentationRequested
familyCommandReceived
remoteCapabilitiesChanged
connectionLost
motionFaultChanged
motionAvailabilityChanged
```

视觉 `PersonObservation` 一般不需要每帧直接送进 AppController；自动跟随应由 `AutoFollowController` 消费，避免 Controller 被高频观测轰炸。

## 3. 主要职责

- 将产品事件转换为 `PetStateMachine` event；
- 根据当前状态启动/停止 Service；
- 决定页面显示；
- 处理 Remote AI 不可用时的降级；
- 处理 Reminder/Emergency 抢占；
- 协调 ReminderAlertPage、提醒语音与用户确认；
- 在高层状态改变时 enable/disable 对应 Feature；
- 将业务 Model 传给页面；
- 统一处理可向用户展示的错误。

## 4. Reminder 主动展示

Reminder 到期不是“导航到 Reminder 管理列表”。推荐：

```text
ReminderService::reminderPresentationRequested
        ↓
AppController
        ├── 记录可恢复的当前页面
        ├── PetStateMachine.Attention = Reminder
        ├── MainWindow → ReminderAlertPage
        └── 请求 Audio/TTS 播放 Reminder voice
```

用户确认：

```text
ReminderAlertPage acknowledgeRequested
或 keywordDetected(ReminderAcknowledge)
        ↓
AppController
        ↓
ReminderService::acknowledge(...)
        ↓
若还有排队 Reminder → 展示下一条
否则 → 恢复提醒前页面
```

AppController 负责“当前语音关键词是否应该解释为提醒确认”的上下文判断，但不在自己内部实现 KWS 字符串匹配、重复间隔或 occurrence 状态机。

`Acknowledged` 与 `Completed` 必须保持业务区分；只有明确的完成动作才调用 `markCompleted`。

Emergency 优先级高于 Reminder。Emergency 抢占后，未确认 Reminder occurrence 保持未确认，由 ReminderService 后续重新安排展示。

## 5. 运动相关职责

AppController 只做高层允许/禁止与抢占，不做视觉闭环。

例如 Emergency：

```text
EmergencyRaised
    ↓
AppController
    ├── PetStateMachine.Attention = Emergency
    ├── MotionService.stop(Emergency)
    ├── disable AutoFollow
    └── cancel normal conversation/action
```

例如 Sleep：

```text
SleepRequested
→ MotionService stop/disable
→ PetStateMachine = Sleep
```

自动跟随的连续控制仍是：

```text
PerceptionService
→ AutoFollowController
→ MotionService
```

而不是经过 AppController 每帧转发。

## 6. 不负责

```text
QPainter
SQL
Reminder repeat interval calculation
OrtSession
sherpa API
ALSA PCM
Socket framing
UART bytes
PWM
AutoFollow steering math
```

这些必须下沉。

## 7. 示例：语音入口

```text
KeywordSpottingService::keywordDetected
        ↓
AppController
        ↓
PetStateMachine::dispatch(WakeKeywordDetected)
        ↓
VoiceInteractionService::start()
```

这里的 `WakeKeywordDetected` 与 `PetStateMachine` 文档中的事件命名保持一致。实际代码中建议把事件定义集中在状态机头文件，而不是多个模块各写一套字符串名称。

Reminder 确认关键词是上下文相关语义：ReminderAlertPage 不可见时，不应把普通“知道了”映射到 ReminderService。

## 8. 示例：远端服务器断开

```text
RemoteAiService::serverUnavailable
        ↓
AppController
        ├── 若存在 LocalLanguageService → 使用本地降级
        ├── 若是固定关键词功能 → 本地执行
        └── 否则 → 明确提示“高级语音暂不可用”
```

不能让页面永久停在 Thinking。

Reminder 屏幕显示和触摸确认也不能依赖远端 AI；远端不可用时仍必须完成本地提醒闭环。

## 9. 防止 Controller 膨胀

如果出现以下代码，应继续下沉：

```text
Reminder 调度/重复策略/统计 → Reminder/Care Service
Reminder 音频解码/TTS → Audio/Voice Service
远端语音会话细节 → VoiceInteractionService
协议重连 → Connectivity
机器人协议 → RobotService/Driver
底盘 owner/限速/watchdog → MotionService
视觉跟随控制 → AutoFollowController
```

Controller 保留“什么时候允许谁工作、发生重大状态变化后调用谁”，而不是“怎么实现能力”。

## 10. 版本建议

V0.2 开始引入；V0.3 后成为正式业务入口。ReminderAlertPage 可作为 V0.2 上机适配增量加入，语音确认在 V0.3 KWS 接入后启用。运动模块加入后只增加少量高层协调逻辑，不承接高频运动控制循环。