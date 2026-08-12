# Services

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

Service 层提供稳定业务能力，不直接持有 QWidget，也不暴露底层第三方库或硬件协议细节。

## 建议服务

- [AudioService](AudioService.md)：统一占有麦克风/扬声器数据通道。
- [KeywordSpottingService](KeywordSpottingService.md)：本地关键词/唤醒词。
- [VoiceInteractionService](VoiceInteractionService.md)：一次完整语音交互会话。
- [PerceptionService](PerceptionService.md)：人体与手势感知，输出语义观测。
- [LocalLanguageService](LocalLanguageService.md)：可选本地小语言模型。
- [ReminderService](ReminderService.md)：Reminder 业务。
- [CareService](CareService.md)：关怀摘要与事件聚合。
- [RobotService](RobotService.md)：非底盘的宠物表现/执行器动作。
- [MotionService](MotionService.md)：小车底盘高层运动、安全门与控制权仲裁。
- [RemoteAiService](RemoteAiService.md)：远端高性能 AI 能力统一入口。
- [FamilyLinkService](FamilyLinkService.md)：家属端业务同步。
- [ConnectivityManager](ConnectivityManager.md)：链路/端点可用性。
- [SettingsService](SettingsService.md)：设置业务。
- [SystemService](SystemService.md)：设备状态摘要。

## RobotService 与 MotionService 的边界

```text
RobotService
→ 点头、姿态、轻量角色动作、非底盘执行器

MotionService
→ 前进、后退、转向、停车、自动跟随底盘控制
```

即使这些执行器最终都由同一块 MCU 控制，软件职责仍建议分开，因为底盘移动需要额外的安全、watchdog、控制权和限速策略。

## 原则

Service 可以依赖 Data、Platform、Connectivity，但不能直接切换页面。重计算任务不能默认各自开一堆线程；视觉输出也不能直接越过 MotionService 操作底盘。