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

## 抢占

```text
EmergencyRaised
 ↓
AppController
 ↓
PetStateMachine.Attention = Emergency
 ↓
cancel/defer normal conversation
 ↓
VoiceInteractionService.cancel
RobotService.stopMotion
 ↓
PetBehaviorController = Alert
MainWindow = EmergencyPage
```

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