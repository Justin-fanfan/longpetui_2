# 文档包清单

[← 根目录](README.md)

本交付分支只包含 LongPet 架构 Markdown 文档，不包含 UI 源码。

## 顶层入口

- [README.md · 总体架构与可点击树](README.md)
- [ARCHITECTURE_RULES.md · 架构决策与约束](ARCHITECTURE_RULES.md)
- [CLASS_INDEX.md · 类/文件快速索引](CLASS_INDEX.md)
- `MANIFEST.md` · 当前文档

## 模块目录

- [01-device/ · 宠物本体](01-device/README.md)
- [02-external/ · 外部系统边界](02-external/README.md)
- [03-flows/ · 关键数据流](03-flows/README.md)
- [04-runtime/ · 运行时、性能与可靠性](04-runtime/README.md)
- [05-build/ · 构建、配置与部署](05-build/README.md)
- [06-roadmap/ · 版本演进](06-roadmap/README.md)

`01-device/` 继续细分为：

- [app/](01-device/app/README.md)
- [ui/](01-device/ui/README.md)
- [model/](01-device/model/README.md)
- [services/](01-device/services/README.md)
- [data/](01-device/data/README.md)
- [platform/](01-device/platform/README.md)
- [connectivity/](01-device/connectivity/README.md)
- [features/](01-device/features/README.md)

## 运动模块重点文档

本轮加入并联动审查了“小车由 MCU 直接控制、龙芯间接控制、后续视觉自动跟随”的架构：

- [MotionModels](01-device/model/MotionModels.md)
- [MotionService](01-device/services/MotionService.md)
- [AutoFollowController](01-device/features/AutoFollowController.md)
- [运动 MCU 边界](01-device/platform/MotionMcuBoundary.md)
- [视觉自动跟随 → 小车运动](03-flows/AutoFollowMotionFlow.md)
- [运动安全与控制权](04-runtime/MotionSafetyAndControl.md)

同时同步修订了：

- [AppController](01-device/app/AppController.md)
- [PetStateMachine](01-device/app/PetStateMachine.md)
- [PetBehaviorController](01-device/app/PetBehaviorController.md)
- [PerceptionService](01-device/services/PerceptionService.md)
- [RobotService](01-device/services/RobotService.md)
- [UartRobotDriver](01-device/platform/UartRobotDriver.md)
- [Emergency Flow](03-flows/EmergencyFlow.md)
- [性能与推理调度](04-runtime/PerformanceAndInferenceScheduling.md)
- [降级与故障恢复](04-runtime/DegradationAndRecovery.md)
- [安全与隐私](04-runtime/SecurityAndPrivacy.md)
- [测试策略](05-build/TestingStrategy.md)
- [版本路线](06-roadmap/VersionRoadmap.md)
- [迁移检查清单](06-roadmap/MigrationChecklist.md)

## Markdown 导航约束

真正需要点击的相对链接必须写在普通 Markdown 内容中，例如：

```markdown
- [AppController](01-device/app/AppController.md)
```

不要把“要点击的链接”放在 fenced code block 中。代码块中的 `[text](path)` 只会显示成纯文本，不会被 GitHub 或 VS Code Markdown Preview 渲染成超链接。

根 README 的长期目录使用嵌套 Markdown 列表，因此目录层级清楚，同时每一项都可点击。