# 关键数据流

[← 根目录](../README.md)

架构最容易通过完整调用链理解。

- [启动与 Companion](StartupAndCompanion.md)
- [远端语音交互](RemoteVoiceFlow.md)
- [远端不可用时的本地降级](OfflineFallbackFlow.md)
- [人体/手势创意互动](PerceptionGestureFlow.md)
- [Reminder / Care](ReminderCareFlow.md)
- [家属端同步](FamilySyncFlow.md)
- [Emergency 抢占](EmergencyFlow.md)

每条链路都遵守：

```text
事件 → Application → Service → Adapter/Data
```

而不是模块之间任意互调。