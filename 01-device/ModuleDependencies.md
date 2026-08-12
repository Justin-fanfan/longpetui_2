# 模块依赖与禁止依赖

[← 宠物本体](README.md)

## 推荐依赖

```text
ui ───────────────┐
                  ▼
               app/controller
                  │
                  ▼
               services
          ┌───────┼──────────┐
          ▼       ▼          ▼
        data   platform  connectivity
          ▲       ▲          ▲
          └──── model/DTO ────┘
```

## 允许

```text
Page → emit signal
AppController → Service
Service → Repository
Service → Platform adapter
Service → Connectivity client
PetBehaviorController → RobotService / UI presentation API
```

## 禁止

```text
HomePage → sherpa
CarePage → SQLite
VisionService → MainWindow::showEmergency()
AiServerClient → PetFaceWidget
UartRobotDriver → PetStateMachine
Electron → SQLite raw table
Remote AI Server → QWidget
```

## 为什么

保持这些边界后：

- UI 可以在 Windows 用假数据调试；
- AI Server 协议变化不影响页面；
- SQLite schema 改动不影响 Electron UI；
- 本地模型从 Python 换 C++ 时 Service API 可以不变；
- Robot Driver 换协议不影响 PetBehaviorController；
- 断网时 AppController 可以统一执行降级。

## 不使用全局 EventBus

Qt signal/slot 已够用。不要为了“解耦”再引入一个所有模块都能发任意字符串事件的全局总线，否则类型和调用链会重新变得不可追踪。