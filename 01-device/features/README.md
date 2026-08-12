# 本地创意功能

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

LongPet 的产品差异化不应只来自“大模型”，还来自把本体已有能力组合成可靠、有角色感的互动。

- [CreativeFeatureCoordinator](CreativeFeatureCoordinator.md)
- [AutoFollowController](AutoFollowController.md)：视觉观测到小车运动意图的自动跟随控制。
- [FeatureExamples](FeatureExamples.md)

## 与运动模块的边界

创意功能可以决定：

```text
“现在希望跟随用户”
“现在希望朝向用户”
```

但不能直接发送 PWM/UART。

自动跟随必须经过：

```text
PerceptionService
→ AutoFollowController
→ MotionService
→ MCU Driver
```

第一版不需要动态 Plugin Framework。先使用普通 Coordinator；只有独立功能明显增多后再拆成单独 Feature 类。