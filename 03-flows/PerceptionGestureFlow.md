# 人体 / 手势 → 本地创意互动

[← Flows](README.md)

```text
CameraCapture
 ↓ latest frame
PerceptionService
 ├── person detection
 └── gesture recognition
 ↓ debounce / temporal confirmation
GestureEvent
 ↓
CreativeFeatureCoordinator
 ↓
AppController / PetStateMachine policy
 ↓
PetBehaviorController
 ├── PetFaceWidget expression
 └── RobotService action
```

## 示例：挥手

```text
Wave confirmed
+ current state = Companion
+ no Emergency
→ Playful expression
→ lookAtUser
→ nod
```

## 如果正在 Listening

低优先级挥手互动不应抢占当前语音会话。

FeatureCoordinator 只产生 intent，由 StateMachine/Controller 决定是否执行或忽略。

## 性能

- 视觉只取最新帧；
- 初始 2～5 inference FPS；
- active voice/local LLM 时可降频；
- 每帧结果不写 SQLite。