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

## V0.4：人体 / 手势 / 运动底盘 / Robot / 本地创意功能

建议分两个小阶段，不要视觉和运动第一次接入就直接做自动跟随。

### V0.4-A：感知与底盘基础链路

增加：

```text
CameraCapture
PerceptionService
OrtVisionEngine
RobotService
MotionService
UartRobotDriver / MCU protocol adapter
MotionModels
Motion MCU watchdog / telemetry
PetBehaviorController
```

先完成：

```text
人体/手势识别
低速固定运动命令
Stop / Emergency Stop
龙芯进程退出 → MCU 自动停车
通信断开 → MCU 自动停车
MCU reset-safe
```

目标：

> “视觉”和“底盘”分别先成为可靠能力。

### V0.4-B：视觉自动跟随与创意功能

增加：

```text
AutoFollowController
CreativeFeatureCoordinator
AutoFollowMotionFlow
```

建议开发顺序：

```text
目标稳定观测
→ 只转向对人
→ target lost stop
→ 低速前后跟随
→ 更完整传感器/避障融合
```

目标：宠物真正具有“看见用户、理解简单手势、产生统一屏幕/实体回应，并可在受控条件下低速跟随”的角色感。

注意：基础人体检测 + 跟随控制不等于完整自主导航。没有可靠避障能力时，自动跟随只按低速、受控场景功能开发。

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

默认不提供远程驾驶小车权限；如果未来需要，应作为独立安全功能重新设计。

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
- Motion control ownership；
- MCU heartbeat/watchdog；
- AutoFollow target loss / stale observation；
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
motion safety
MCU fail-safe
security boundary
long-run stability
```

开发/比赛 Engineering UI 与老人日常 UI 保持隔离。