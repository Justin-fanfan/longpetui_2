# V0.1 → V1.0 路线

[← Roadmap](README.md)

## V0.1：正式 UI 骨架

实现：

```text
main.cpp
MainWindow
CompanionPage
HomePage
PetFaceWidget
VisualComponents
VisualTokens
QSS
Touch reveal
Control timeout
```

目标：从 `longpetui_2` 提取视觉底座，建立正式产品外壳。

不建立完整 Service 树。

---

## V0.2：SQLite / Reminder / Care / Settings

增加：

```text
Application（可开始）
AppController
DatabaseManager
ReminderRepository
CareEventRepository
SettingsRepository
ReminderService
CareService
SettingsService
Reminder/Care/Settings Pages
```

目标：第一批真正本地业务闭环。

---

## V0.3：本地 KWS + Remote AI Speech

增加：

```text
PetStateMachine
AudioService
KeywordSpottingService
VoiceInteractionService（复杂后提取）
RemoteAiService
AiServerClient
ITransport
NetworkTransport
BluetoothTransport（实际链路准备好后）
ConversationPage
```

可选：

```text
LocalLanguageService
AiCapabilityPolicy
```

目标：

> 本地关键词入口 + 外部服务器完整 ASR/TTS/推理 + 清楚的离线降级。

---

## V0.4：人体 / 手势 / Robot / 本地创意功能

增加：

```text
CameraCapture
PerceptionService
OrtVisionEngine
RobotService
UartRobotDriver
PetBehaviorController
CreativeFeatureCoordinator
```

目标：宠物真正具有“看见用户、理解简单手势、产生统一屏幕/实体回应”的角色感。

---

## V0.5：家属 Electron 联动

增加：

```text
FamilyLinkService
FamilyGateway
Pairing
Family protocol
DeviceSummary
CareSummary sync
Remote Reminder/Settings
```

目标：家属安全查看/配置，而不是远程访问数据库。

---

## V0.6～V0.9：整机融合

重点：

- Network/Bluetooth fallback；
- AI capability negotiation；
- session timeout/cancel；
- UI + KWS + Vision 组合负载；
- Local LLM 是否值得保留；
- SQLite migration/retention；
- Family 冲突处理；
- Robot failure fallback；
- Emergency priority；
- 长时间稳定运行。

只有实测出现本地 inference 竞争后再加入 `InferenceScheduler`。

---

## V1.0：稳定产品/比赛完整形态

要求：

```text
local autonomy
remote AI enhancement
family management
fault degradation
performance budget
security boundary
long-run stability
```

开发/比赛 Engineering UI 与老人日常 UI 保持隔离。