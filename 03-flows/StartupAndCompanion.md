# 启动与 Companion

[← Flows](README.md)

## 启动

```text
QApplication
 ↓
Application.initialize
 ↓
RuntimeConfig / Logging
 ↓
DatabaseManager.open + migrate
 ↓
Audio/Platform initialize
 ↓
Services create
 ↓
MainWindow create
 ↓
connect signals
 ↓
PetStateMachine = Companion
 ↓
PetBehaviorController
 ├── PetFace = DefaultOpen
 └── Robot = idle
 ↓
KWS start
 ↓
后台尝试 AI Server / Family connectivity
```

远端连接必须后台进行，不能让首屏等网络。

## 触摸进入 Control

```text
CompanionPage::controlRequested
 ↓
AppController
 ↓
PetStateMachine: Companion → Control
 ↓
MainWindow: HomePage
```

## 无操作返回

```text
Control inactivity timeout
 ↓
AppController / V0.1 MainWindow
 ↓
Control → Companion
```

只有 Control 页重置该 timeout。Listening/Thinking/Speaking 不使用同一个 UI inactivity timer。