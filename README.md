# LongPet 宠物端整体软件架构

> 面向龙芯 2K0300 宠物终端的长期架构说明。  
> 本文档树以“宠物本体软件”为中心，同时定义与外部龙芯 AI 推理服务器、家属 Electron 应用的边界。  
> 当前阶段：V0.1 UI 正式工程准备期。

---

## 1. 项目整体情况

LongPet 是一个以龙芯 2K0300 为本体计算平台的适老陪伴机器宠物。

宠物本体需要逐步具备：

- Qt 6 Widgets UI 与触摸；
- 宠物表情和低 CPU 动画；
- 基础人体识别；
- 基础手势识别；
- SQLite 本地数据；
- 本地语音关键词/唤醒词识别；
- 可选几十 MB 级本地小语言模型；
- 宠物高层状态机；
- Reminder、Care、本地互动等创意功能；
- 实体宠物动作/外设控制；
- Network/Bluetooth 通信。

系统另有两个外部节点：

### 龙芯高性能 AI 推理服务器

宠物通过网络或蓝牙连接后，可将会话音频发送给服务器，由服务器提供更高质量的 ASR、语言推理和 TTS，并返回识别文本、回复文本、生成音频等。

### 家属 Electron 应用

通过网络与宠物通信，用于查看经过授权的宠物/Care/Reminder/设备状态，并下发 Reminder 和允许的设置。

因此整个系统的定位是：

> **本地自治优先，远端 AI 增强，家属端安全管理。**

---

## 2. 总体架构原则

宠物本体内部依赖方向：

```text
UI
 ↓
Application / PetStateMachine
 ↓
Domain Services
 ↓
Data / Platform / Connectivity
 ↓
Linux / Hardware / Third-party Libraries
```

系统级原则：

1. AI Server 断开后，宠物仍保留 UI、KWS、Reminder、SQLite、基础视觉、Robot 和本地创意功能；
2. 家属端不直接访问 SQLite，不直接控制 UART/GPIO；
3. 本地 KWS 是常态语音入口，完整 ASR/TTS 优先由远端 AI Server 按会话提供；
4. 可选本地小语言模型只做离线增强，不成为基础依赖；
5. 状态机管理用户可感知的高层交互状态，不把网络/人体存在等上下文组合成状态爆炸；
6. Qt UI 不执行重推理；
7. 2K0300 单核环境下，本地重推理必须按优先级调度；
8. Transport、模型、数据库和硬件实现均隔离在稳定边界之后。

详细规则见 [架构决策与约束](ARCHITECTURE_RULES.md)。

---

## 3. 系统上下文

```text
                         ┌──────────────────────────┐
                         │ 龙芯高性能 AI Server      │
                         │ ASR / TTS / LLM / AI     │
                         └────────────┬─────────────┘
                                      │ Network / Bluetooth
                                      │
┌─────────────────────────────────────▼──────────────────────────────────────┐
│                           LongPet 宠物本体                                 │
│                                                                            │
│ UI → App/StateMachine → Services → Data/Platform/Connectivity             │
│                                                                            │
│ Local: KWS / Vision / Gesture / SQLite / Robot / Optional small LLM       │
└─────────────────────────────────────┬──────────────────────────────────────┘
                                      │ Network
                                      │
                         ┌────────────▼─────────────┐
                         │ 家属 Electron 应用        │
                         │ 查看 / Reminder / 设置    │
                         └──────────────────────────┘
```

---

## 4. 可点击的长期源码 / 模块目录

> 这是**长期目标目录**，不是要求 V0.1 一次性创建全部文件。  
> 点击目录或类名即可进入职责、依赖、线程、数据流、版本建议等详细说明。

```text
LongPet/
├── [src / 宠物本体](01-device/README.md)
│   ├── [模块依赖规则](01-device/ModuleDependencies.md)
│   │
│   ├── [app/](01-device/app/README.md)
│   │   ├── [Application / main.cpp](01-device/app/Application.md)
│   │   ├── [AppController](01-device/app/AppController.md)
│   │   ├── [AppState](01-device/app/AppState.md)
│   │   ├── [PetStateMachine](01-device/app/PetStateMachine.md)
│   │   ├── [PetBehaviorController](01-device/app/PetBehaviorController.md)
│   │   └── [AiCapabilityPolicy](01-device/app/AiCapabilityPolicy.md)
│   │
│   ├── [ui/](01-device/ui/README.md)
│   │   ├── [MainWindow](01-device/ui/MainWindow.md)
│   │   ├── [longpetui_2 → 正式工程迁移](01-device/ui/UIPrototypeMigration.md)
│   │   ├── [pages/](01-device/ui/pages/README.md)
│   │   │   ├── [CompanionPage](01-device/ui/pages/CompanionPage.md)
│   │   │   ├── [HomePage](01-device/ui/pages/HomePage.md)
│   │   │   ├── [ConversationPage](01-device/ui/pages/ConversationPage.md)
│   │   │   ├── [CarePage](01-device/ui/pages/CarePage.md)
│   │   │   ├── [ReminderPage](01-device/ui/pages/ReminderPage.md)
│   │   │   ├── [ReminderEditPage](01-device/ui/pages/ReminderEditPage.md)
│   │   │   ├── [SettingsPage](01-device/ui/pages/SettingsPage.md)
│   │   │   ├── [EmergencyPage](01-device/ui/pages/EmergencyPage.md)
│   │   │   └── [SleepPage](01-device/ui/pages/SleepPage.md)
│   │   └── [widgets/](01-device/ui/widgets/README.md)
│   │       ├── [PetFaceWidget](01-device/ui/widgets/PetFaceWidget.md)
│   │       ├── [VisualComponents](01-device/ui/widgets/VisualComponents.md)
│   │       ├── [VisualTokens](01-device/ui/widgets/VisualTokens.md)
│   │       └── [QSS / Resources](01-device/ui/widgets/QSSAndResources.md)
│   │
│   ├── [model/](01-device/model/README.md)
│   │   ├── [Reminder / Care Models](01-device/model/ReminderModels.md)
│   │   ├── [Perception Models](01-device/model/PerceptionModels.md)
│   │   ├── [Speech / AI Models](01-device/model/SpeechModels.md)
│   │   └── [Device / Family DTO](01-device/model/DeviceAndFamilyModels.md)
│   │
│   ├── [services/](01-device/services/README.md)
│   │   ├── [AudioService](01-device/services/AudioService.md)
│   │   ├── [KeywordSpottingService](01-device/services/KeywordSpottingService.md)
│   │   ├── [VoiceInteractionService](01-device/services/VoiceInteractionService.md)
│   │   ├── [PerceptionService](01-device/services/PerceptionService.md)
│   │   ├── [LocalLanguageService](01-device/services/LocalLanguageService.md)
│   │   ├── [ReminderService](01-device/services/ReminderService.md)
│   │   ├── [CareService](01-device/services/CareService.md)
│   │   ├── [RobotService](01-device/services/RobotService.md)
│   │   ├── [RemoteAiService](01-device/services/RemoteAiService.md)
│   │   ├── [FamilyLinkService](01-device/services/FamilyLinkService.md)
│   │   ├── [ConnectivityManager](01-device/services/ConnectivityManager.md)
│   │   ├── [SettingsService](01-device/services/SettingsService.md)
│   │   └── [SystemService](01-device/services/SystemService.md)
│   │
│   ├── [data/](01-device/data/README.md)
│   │   ├── [DatabaseManager](01-device/data/DatabaseManager.md)
│   │   ├── [Repositories](01-device/data/Repositories.md)
│   │   ├── [SQLite Schema](01-device/data/SQLiteSchema.md)
│   │   └── [持久化规则](01-device/data/PersistenceRules.md)
│   │
│   ├── [platform/](01-device/platform/README.md)
│   │   ├── [AlsaAudioDevice](01-device/platform/AlsaAudioDevice.md)
│   │   ├── [CameraCapture](01-device/platform/CameraCapture.md)
│   │   ├── [LocalInference / ORT / sherpa](01-device/platform/LocalInference.md)
│   │   ├── [UartRobotDriver](01-device/platform/UartRobotDriver.md)
│   │   └── [可选 Python AI Worker](01-device/platform/PythonWorkerOption.md)
│   │
│   ├── [connectivity/](01-device/connectivity/README.md)
│   │   ├── [ITransport](01-device/connectivity/ITransport.md)
│   │   ├── [NetworkTransport](01-device/connectivity/NetworkTransport.md)
│   │   ├── [BluetoothTransport](01-device/connectivity/BluetoothTransport.md)
│   │   ├── [AiServerClient](01-device/connectivity/AiServerClient.md)
│   │   ├── [FamilyGateway](01-device/connectivity/FamilyGateway.md)
│   │   └── [通信协议 / 消息模型](01-device/connectivity/Protocol.md)
│   │
│   └── [features/](01-device/features/README.md)
│       ├── [CreativeFeatureCoordinator](01-device/features/CreativeFeatureCoordinator.md)
│       └── [本地创意功能示例](01-device/features/FeatureExamples.md)
│
├── [外部系统边界](02-external/README.md)
│   ├── [龙芯 AI 推理服务器边界](02-external/AIServerBoundary.md)
│   └── [家属 Electron 应用边界](02-external/FamilyAppBoundary.md)
│
├── [关键数据流](03-flows/README.md)
│   ├── [启动与 Companion](03-flows/StartupAndCompanion.md)
│   ├── [Remote Voice：KWS → ASR → 推理 → TTS](03-flows/RemoteVoiceFlow.md)
│   ├── [Remote AI 离线降级](03-flows/OfflineFallbackFlow.md)
│   ├── [人体 / 手势互动](03-flows/PerceptionGestureFlow.md)
│   ├── [Reminder / Care](03-flows/ReminderCareFlow.md)
│   ├── [Family Sync](03-flows/FamilySyncFlow.md)
│   └── [Emergency 抢占](03-flows/EmergencyFlow.md)
│
├── [运行时 / 性能 / 可靠性](04-runtime/README.md)
│   ├── [线程模型](04-runtime/ThreadModel.md)
│   ├── [音频流水线](04-runtime/AudioPipeline.md)
│   ├── [单核性能与推理调度](04-runtime/PerformanceAndInferenceScheduling.md)
│   ├── [降级与故障恢复](04-runtime/DegradationAndRecovery.md)
│   ├── [安全与隐私](04-runtime/SecurityAndPrivacy.md)
│   └── [日志与可观测性](04-runtime/ObservabilityAndLogging.md)
│
├── [构建 / 配置 / 部署](05-build/README.md)
│   ├── [长期源码目录](05-build/ProjectLayout.md)
│   ├── [CMake 演进](05-build/CMakeStrategy.md)
│   ├── [运行时配置](05-build/Configuration.md)
│   ├── [2K0300 部署](05-build/Deployment.md)
│   └── [测试策略](05-build/TestingStrategy.md)
│
└── [版本演进](06-roadmap/README.md)
    ├── [V0.1 → V1.0 路线](06-roadmap/VersionRoadmap.md)
    └── [迁移检查清单](06-roadmap/MigrationChecklist.md)
```

另外提供 [类/文件快速索引](CLASS_INDEX.md)。

---

## 5. 推荐阅读顺序

第一次阅读：

```text
README.md
→ 01-device/README.md
→ 01-device/app/PetStateMachine.md
→ 01-device/services/README.md
→ 02-external/README.md
→ 03-flows/RemoteVoiceFlow.md
→ 04-runtime/PerformanceAndInferenceScheduling.md
→ 06-roadmap/VersionRoadmap.md
```

开发具体功能时，直接从第四节进入对应类。

---

## 6. 当前阶段

V0.1 正式工程仍只需要一个很小的骨架：

```text
main.cpp
MainWindow
CompanionPage
HomePage
PetFaceWidget
VisualComponents
VisualTokens
QSS / Resources
```

文档中的其他类不是“现在必须创建的空架构”，而是后续真实功能进入时的明确落点。