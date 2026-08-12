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
reminderTriggered
familyCommandReceived
remoteCapabilitiesChanged
connectionLost
```

## 3. 主要职责

- 将事件转换为 `PetStateMachine` event；
- 根据当前状态启动/停止 Service；
- 决定页面显示；
- 处理 Remote AI 不可用时的降级；
- 处理 Reminder/Emergency 抢占；
- 将业务 Model 传给页面；
- 统一处理可向用户展示的错误。

## 4. 不负责

```text
QPainter
SQL
OrtSession
sherpa API
ALSA PCM
Socket framing
UART bytes
```

这些必须下沉。

## 5. 示例：语音入口

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

## 6. 示例：远端服务器断开

```text
RemoteAiService::serverUnavailable
        ↓
AppController
        ├── 若存在 LocalLanguageService → 使用本地降级
        ├── 若是固定关键词功能 → 本地执行
        └── 否则 → 明确提示“高级语音暂不可用”
```

不能让页面永久停在 Thinking。

## 7. 防止 Controller 膨胀

如果出现以下代码，应继续下沉：

```text
Reminder 统计 → Reminder/Care Service
远端语音会话细节 → VoiceInteractionService
协议重连 → Connectivity
机器人协议 → RobotService/Driver
```

Controller 保留“什么时候调用谁”，而不是“怎么实现能力”。

## 8. 版本建议

V0.2 开始引入；V0.3 后成为正式业务入口。