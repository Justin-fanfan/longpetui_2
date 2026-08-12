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
PetBehaviorController → RobotService / UI presentation API
```

## 禁止

```text
HomePage → sherpa
CarePage → SQLite
Vision/PerceptionService → MainWindow::showEmergency()
AiServerClient → PetFaceWidget
UartRobotDriver → PetStateMachine
Electron → SQLite raw table
Remote AI Server → QWidget
Model/DTO → Service/QWidget/DatabaseManager
```

## 为什么

保持这些边界后：

- UI 可以在 Windows 用假数据调试；
- AI Server 协议变化不影响页面；
- SQLite schema 改动不影响 Electron UI；
- 本地模型从 Python 换 C++ 时 Service API 可以不变；
- Robot Driver 换协议不影响 PetBehaviorController；
- 断网时 AppController 可以统一执行降级；
- Model 保持轻量后，跨线程和单元测试更简单。

## 不使用全局 EventBus

Qt signal/slot 已够用。不要为了“解耦”再引入一个所有模块都能发任意字符串事件的全局总线，否则类型和调用链会重新变得不可追踪。