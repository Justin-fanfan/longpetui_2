# Services

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

Service 层提供稳定业务能力，不直接持有 QWidget，也不暴露底层第三方库细节。

## 建议服务

- [AudioService](AudioService.md)：统一占有麦克风/扬声器数据通道。
- [KeywordSpottingService](KeywordSpottingService.md)：本地关键词/唤醒词。
- [VoiceInteractionService](VoiceInteractionService.md)：一次完整语音交互会话。
- [PerceptionService](PerceptionService.md)：人体与手势感知。
- [LocalLanguageService](LocalLanguageService.md)：可选本地小语言模型。
- [ReminderService](ReminderService.md)
- [CareService](CareService.md)
- [RobotService](RobotService.md)
- [RemoteAiService](RemoteAiService.md)：远端高性能 AI 能力统一入口。
- [FamilyLinkService](FamilyLinkService.md)：家属端业务同步。
- [ConnectivityManager](ConnectivityManager.md)：链路/端点可用性。
- [SettingsService](SettingsService.md)
- [SystemService](SystemService.md)

## 原则

Service 可以依赖 Data、Platform、Connectivity，但不能直接切换页面。重计算任务也不能默认各自开一堆线程。