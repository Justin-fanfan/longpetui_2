# PerceptionService

[← Services](README.md)

## 1. 定位

本体基础视觉感知统一入口：

- 人体/人员存在检测；
- 基础人体识别（按实际模型定义）；
- 手势识别；
- 为自动跟随提供稳定的人员观测；
- 后续必要的轻量安全感知。

## 2. 输入

来自 `CameraCapture` 的“最新帧”。

## 3. 输出

```cpp
signals:
    void humanPresenceChanged(bool present);
    void personObservationUpdated(PersonObservation);
    void gestureRecognized(GestureEvent);
```

`PersonObservation` 可以包含：

```text
bounding box / center
confidence
timestamp
optional target id / track id
optional distance estimate
```

但它只描述“看到了什么”，不描述“电机应该怎样转”。

## 4. 与自动跟随的边界

正确：

```text
PerceptionService
→ PersonObservation
→ AutoFollowController
→ MotionIntent
→ MotionService
→ MCU
```

禁止：

```text
PerceptionService
→ UartRobotDriver
```

视觉模型误检、抖动或短时丢帧不能直接变成底盘命令。

## 5. Debounce / Tracking Stability

模型可能连续几十帧识别出同一挥手动作，也可能人体框短时跳动。Service 应提供必要的语义稳定化：

- confidence threshold；
- temporal confirmation；
- gesture cooldown；
- observation timestamp；
- 可选轻量 track continuity。

手势输出“一个语义事件”；人体跟踪输出“最新有效观测”。

## 6. 单核策略

- 不跟随相机原始 FPS 全速推理；
- 起步建议 2～5 inference FPS；
- active voice/local LLM 时可降低普通视觉频率；
- 只处理最新帧，不积压旧帧；
- 自动跟随控制器消费最新观测，而不是积压历史 observation。

## 7. 数据记录

普通每帧 `PersonObservation` 不进入 SQLite。只有有产品价值的事件才由 Care/Feature 层决定是否记录。

## 8. 安全说明

基础人体检测/手势模型不是完整自主导航系统，也不能替代近场避障和 MCU watchdog。

如果未来用于自动跟随，应按 [AutoFollowController](../features/AutoFollowController.md) 和 [运动安全与控制权](../../04-runtime/MotionSafetyAndControl.md) 的约束实现。

## 9. 不负责

- 切 UI；
- Emergency 页面；
- Robot/Motion UART；
- 电机速度计算；
- Family 网络协议。

## 10. 引入版本

V0.4 或视觉功能实际开发时。