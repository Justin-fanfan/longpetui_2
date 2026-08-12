# Emergency 抢占流程

[← Flows](README.md)

## 可能来源

```text
可靠的视觉/传感规则
用户主动求助
本地规则
家属允许的远程命令（若产品定义）
```

不要让通用 LLM 的自由文本单独成为安全告警唯一依据。

## 抢占顺序

如果底盘可能正在移动，Emergency 的第一优先级是停止真实运动：

```text
EmergencyRaised
 ↓
AppController
 ↓
PetStateMachine.Attention = Emergency
 ↓
MotionService.stop(Emergency)
 ↓
cancel/defer normal conversation
 ↓
VoiceInteractionService.cancel
RobotService cancel/stop normal action
 ↓
PetBehaviorController = Alert
MainWindow = EmergencyPage
```

运动停止不能等待：

```text
Remote AI
SQLite
TTS
UI animation
```

完成。

## MCU 层

龙芯发出 Emergency/Stop 后，MCU 应优先执行停车。

即使龙芯应用在 Emergency 前后崩溃，MCU 也必须依靠 heartbeat/watchdog timeout 自行进入停止状态。

## AutoFollow

Emergency 到达时：

```text
AutoFollowController → SafetyStopped/Disabled
MotionService → force stop
```

解除 Emergency 后**不要自动恢复之前的跟随运动**。应回到停止状态，由明确的新用户/产品事件重新启用。

## 用户确认安全

```text
EmergencyPage::userConfirmedSafe
 ↓
AppController
 ↓
clear Emergency
 ↓
回 Companion 或明确恢复策略
```

底盘仍保持 stopped，除非之后重新获得合法 motion owner。

## 联系家属

```text
contactFamilyRequested
 ↓
FamilyLinkService / allowed notification channel
 ↓
result
```

EmergencyPage 不直接发网络请求。

## 可靠性

如果 Family Link 不可用，UI 仍应明确告诉用户联系失败，而不是卡住页面。

如果 Motion MCU 不可达，也应记录/展示设备运动模块故障，但不能因此阻塞 Emergency UI。