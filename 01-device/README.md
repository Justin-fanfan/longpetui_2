# LongPet 宠物本体软件

[← 根目录](../README.md)

宠物本体是整个系统的自治核心。外部 AI Server 和家属 Electron 应用都属于“可连接能力”，不能成为宠物能否正常启动和执行基本功能的硬依赖。

## 本体必须独立保留的能力

```text
Qt UI + touch
PetStateMachine
local keyword spotting
basic person / gesture perception
SQLite
Reminder / Care
basic Robot behavior
basic chassis control through MCU
local creative features
connection management
```

可选：

```text
几十 MB 级本地小语言模型
```

## 小车运动模块

底盘由单片机直接控制，龙芯板通过高层命令间接控制：

```text
LongPet on 2K0300
→ MotionService
→ MCU protocol driver
→ Motion MCU
→ motor driver / wheels
```

以后视觉自动跟随采用：

```text
PerceptionService
→ AutoFollowController
→ MotionService
→ MCU
```

视觉模型不能直接操作 UART/PWM。

## 模块

- [app/](app/README.md)：产品流程、状态机、行为协调。
- [ui/](ui/README.md)：Qt Widgets 页面与视觉系统。
- [model/](model/README.md)：普通 C++ Model / DTO，包括 Motion 模型。
- [services/](services/README.md)：业务能力，包括 MotionService。
- [data/](data/README.md)：SQLite 与 Repository。
- [platform/](platform/README.md)：ALSA、Camera、ORT/sherpa、Robot Driver、运动 MCU 边界。
- [connectivity/](connectivity/README.md)：Network/Bluetooth、AI Server、Family 通信协议。
- [features/](features/README.md)：本地创意功能组合和 AutoFollowController。

## 进程建议

默认优先一个 LongPet Qt 主进程，配合少量 worker thread。

如果现有 AI 代码大量使用 Python，可选增加**一个长期驻留的 Python AI worker**，不要每次推理临时启动 Python。

底盘实时控制不放 Linux worker 中，而应由运动 MCU 负责。

## 关键边界

```text
UI
 ↓
Application
 ↓
Services / Feature Controllers
 ↓
Model / Data / Platform / Connectivity
```

运动另有明确执行边界：

```text
MotionService → MCU Driver → Motion MCU → Chassis
```

详见 [模块依赖与禁止依赖](ModuleDependencies.md)。