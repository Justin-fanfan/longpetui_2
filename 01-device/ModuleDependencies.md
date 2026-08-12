# 模块依赖与禁止依赖

[← 宠物本体](README.md)

## 推荐依赖

核心调用方向：

```text
UI
 ↓
Application / Controller / StateMachine
 ↓
Services
 ├──→ Data
 ├──→ Platform
 └──→ Connectivity

Model / DTO = 跨边界使用的轻量数据类型
```

`model/` 不应被理解为必须位于调用链最底部的“运行模块”。它主要保存普通 C++ 数据结构/DTO，可按需要被 UI、Application、Service、Data 和 Connectivity 使用，但其中不能反向持有 Service、QWidget、数据库连接或硬件对象。

## 允许

```text
Page → emit signal
Page ← Model/DTO
AppController → Service
AppController ↔ PetStateMachine
Service → Repository
Service → Platform adapter
Service → Connectivity client
Service ↔ Model/DTO
Repository ↔ Model/DTO
Connectivity ↔ protocol DTO
PetBehaviorController → RobotService / MotionService / UI presentation API
PerceptionService → emit PersonObservation
AutoFollowController → MotionService
MotionService → MCU protocol driver
```

## 小车底盘专用链路

```text
CameraCapture
   ↓
PerceptionService
   ↓ PersonObservation
AutoFollowController
   ↓ MotionIntent
MotionService
   ↓ safety / ownership / speed limit
UartRobotDriver / MCU protocol adapter
   ↓
Motion MCU
   ↓ realtime motor control
Chassis
```

每一层只承担一个职责：

- `PerceptionService`：看到了什么；
- `AutoFollowController`：希望怎样移动；
- `MotionService`：现在是否允许这样移动；
- Driver：怎样把受限命令可靠送到 MCU；
- MCU：怎样实时驱动电机，并在失联/异常时停车。

## 禁止

```text
HomePage → sherpa
CarePage → SQLite
Vision/PerceptionService → MainWindow::showEmergency()
PerceptionService → UartRobotDriver / PWM
AutoFollowController → UART bytes / PWM
AiServerClient → PetFaceWidget
UartRobotDriver → PetStateMachine
Electron → SQLite raw table
Electron → motor/PWM command
Remote AI Server → QWidget
Remote AI Server → direct chassis control
Model/DTO → Service/QWidget/DatabaseManager
```

## 为什么

保持这些边界后：

- UI 可以在 Windows 用假数据调试；
- AI Server 协议变化不影响页面；
- SQLite schema 改动不影响 Electron UI；
- 本地模型从 Python 换 C++ 时 Service API 可以不变；
- MCU/Robot Driver 换协议不影响 AutoFollowController；
- 自动跟随误检不会直接越过 MotionService 安全门；
- Linux 进程故障时 MCU watchdog 仍能停车；
- 断网时 AppController 可以统一执行降级；
- Model 保持轻量后，跨线程和单元测试更简单。

## 不使用全局 EventBus

Qt signal/slot 已够用。不要为了“解耦”再引入一个所有模块都能发任意字符串事件的全局总线，否则类型和调用链会重新变得不可追踪。
