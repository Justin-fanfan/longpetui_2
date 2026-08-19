# 类 / 文件快速索引

[← 根目录](README.md)

## Application

- [Application](01-device/app/Application.md)
- [AppController](01-device/app/AppController.md)
- [AppState](01-device/app/AppState.md)
- [PetStateMachine](01-device/app/PetStateMachine.md)
- [PetBehaviorController](01-device/app/PetBehaviorController.md)
- [AiCapabilityPolicy](01-device/app/AiCapabilityPolicy.md)

## UI

- [MainWindow](01-device/ui/MainWindow.md)
- [CompanionPage](01-device/ui/pages/CompanionPage.md)
- [HomePage](01-device/ui/pages/HomePage.md)
- [ConversationPage](01-device/ui/pages/ConversationPage.md)
- [CarePage](01-device/ui/pages/CarePage.md)
- [ReminderPage](01-device/ui/pages/ReminderPage.md)
- [ReminderAlertPage](01-device/ui/pages/ReminderAlertPage.md)
- [ReminderEditPage](01-device/ui/pages/ReminderEditPage.md)
- [SettingsPage](01-device/ui/pages/SettingsPage.md)
- [EmergencyPage](01-device/ui/pages/EmergencyPage.md)
- [SleepPage](01-device/ui/pages/SleepPage.md)
- [PetFaceWidget](01-device/ui/widgets/PetFaceWidget.md)
- [VisualComponents](01-device/ui/widgets/VisualComponents.md)
- [VisualTokens](01-device/ui/widgets/VisualTokens.md)

## Models

- [Reminder / Care Models](01-device/model/ReminderModels.md)
- [Perception Models](01-device/model/PerceptionModels.md)
- [Speech / AI Models](01-device/model/SpeechModels.md)
- [Motion Models](01-device/model/MotionModels.md)
- [Device / Family DTO](01-device/model/DeviceAndFamilyModels.md)

## Services

- [AudioService](01-device/services/AudioService.md)
- [KeywordSpottingService](01-device/services/KeywordSpottingService.md)
- [VoiceInteractionService](01-device/services/VoiceInteractionService.md)
- [PerceptionService](01-device/services/PerceptionService.md)
- [LocalLanguageService](01-device/services/LocalLanguageService.md)
- [ReminderService](01-device/services/ReminderService.md)
- [CareService](01-device/services/CareService.md)
- [RobotService](01-device/services/RobotService.md)
- [MotionService](01-device/services/MotionService.md)
- [RemoteAiService](01-device/services/RemoteAiService.md)
- [FamilyLinkService](01-device/services/FamilyLinkService.md)
- [ConnectivityManager](01-device/services/ConnectivityManager.md)
- [SettingsService](01-device/services/SettingsService.md)
- [SystemService](01-device/services/SystemService.md)

## Platform

- [AlsaAudioDevice](01-device/platform/AlsaAudioDevice.md)
- [CameraCapture](01-device/platform/CameraCapture.md)
- [LocalInference](01-device/platform/LocalInference.md)
- [UartRobotDriver](01-device/platform/UartRobotDriver.md)
- [运动 MCU 边界](01-device/platform/MotionMcuBoundary.md)
- [Python Worker Option](01-device/platform/PythonWorkerOption.md)

## Connectivity

- [ITransport](01-device/connectivity/ITransport.md)
- [NetworkTransport](01-device/connectivity/NetworkTransport.md)
- [BluetoothTransport](01-device/connectivity/BluetoothTransport.md)
- [AiServerClient](01-device/connectivity/AiServerClient.md)
- [FamilyGateway](01-device/connectivity/FamilyGateway.md)
- [Protocol](01-device/connectivity/Protocol.md)

## Features

- [CreativeFeatureCoordinator](01-device/features/CreativeFeatureCoordinator.md)
- [AutoFollowController](01-device/features/AutoFollowController.md)

## 关键流程 / 运行时说明

- [Reminder / Care 数据流](03-flows/ReminderCareFlow.md)
- [视觉自动跟随 → 小车运动](03-flows/AutoFollowMotionFlow.md)
- [运动安全与控制权](04-runtime/MotionSafetyAndControl.md)
- [单核性能与推理调度](04-runtime/PerformanceAndInferenceScheduling.md)
