# 关键数据流

[← 根目录](../README.md)

架构最容易通过完整调用链理解。

- [启动与 Companion](StartupAndCompanion.md)
- [远端语音交互](RemoteVoiceFlow.md)
- [远端不可用时的本地降级](OfflineFallbackFlow.md)
- [人体/手势创意互动](PerceptionGestureFlow.md)
- [视觉自动跟随 → 小车运动](AutoFollowMotionFlow.md)
- [Reminder / Care](ReminderCareFlow.md)
- [家属端同步](FamilySyncFlow.md)
- [Emergency 抢占](EmergencyFlow.md)

每条链路都遵守：

```text
事件 / 观测 → Application / Feature Controller → Service → Adapter / Data
```

对于底盘运动还必须额外经过：

```text
MotionService safety / ownership
→ MCU
```

而不是视觉模型、页面或远端命令直接操作电机。