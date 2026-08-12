# CreativeFeatureCoordinator

[← Features](README.md)

## 定位

协调“多个已有 Service 组合成一个本地创意功能”。

例如：

```text
Gesture Wave
+ Human present
→ Playful face
→ lookAtUser
→ nod
```

## 可以依赖

- PerceptionService；
- Reminder/CareService；
- PetStateMachine；
- PetBehaviorController；
- RobotService；
- LocalLanguageService（可选）；
- 本地规则数据。

## 输出方式

最好输出“Feature intent/event”，再由 AppController/StateMachine 确认是否执行。

这样低优先级创意功能不会越过 Emergency/Reminder 优先级。

## 不负责

- SQL；
- ORT；
- QPainter；
- UART bytes；
- Remote protocol。

## 何时拆 Feature 类

当出现 3～5 个相互独立、各自有状态/定时器的玩法时，可以拆：

```text
WaveGreetingFeature
HydrationNudgeFeature
CompanionIdleFeature
```

在此之前保持一个简单 Coordinator。