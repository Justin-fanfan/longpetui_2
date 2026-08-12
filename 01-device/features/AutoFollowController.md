# AutoFollowController

[← Features](README.md)

## 1. 定位

`AutoFollowController` 是“视觉观测 → 小车运动意图”的控制逻辑。

它不是视觉模型，也不是 MCU Driver。

正确边界：

```text
CameraCapture
   ↓
PerceptionService
   ↓ PersonObservation
AutoFollowController
   ↓ MotionIntent
MotionService
   ↓
MCU
```

## 2. 输入

主要输入：

- 目标人物是否存在；
- 目标在画面中的横向位置；
- 目标大小/距离估计（如果模型或传感器可提供）；
- observation timestamp；
- confidence；
- MotionService 当前可用性；
- 必要安全状态。

如果现阶段视觉只能判断“有人 + 人在左/中/右”，也完全可以先从离散控制开始，不要求一开始就做连续控制。

## 3. 输出

只输出受限的 `MotionIntent`，例如：

```text
Stop
TurnLeftSlow
TurnRightSlow
ForwardSlow
```

或后续：

```text
linearVelocity
angularVelocity
```

绝不输出 PWM、电机寄存器或 UART 字节。

## 4. 推荐内部状态

```text
Disabled
AcquiringTarget
Following
TargetLost
SafetyStopped
```

目标刚出现时不要立即冲过去，应经过连续若干次可靠观测后进入 Following。

## 5. 跟随基本策略

建议第一版采用保守控制：

- 横向 dead zone：人在画面中间时不频繁左右抖动；
- confidence threshold：低置信度不驱动；
- temporal confirmation：连续观测确认；
- speed cap：自动跟随只允许低速；
- command rate limit：不按摄像头原始 FPS 疯狂发运动命令；
- target lost timeout：目标丢失后立即/短延时停车，不盲目前进；
- hysteresis：避免左右边界来回振荡。

## 6. 多人场景

不要简单地“每帧选最大框”然后直接驱动。

至少需要 target lock 概念：

```text
当前跟随目标
→ 尽量保持同一目标
→ 目标丢失
→ 停车并重新 Acquiring
```

是否需要 ReID 取决于后续模型能力，第一版不必过度设计。

## 7. 与安全传感器的关系

视觉跟随不能替代底盘避障。

如果 MCU/底盘具备：

```text
碰撞开关
超声/ToF
轮速异常
其他障碍检测
```

应由 MCU 或 MotionService 的安全链路优先阻止运动。

如果当前硬件没有可靠避障能力，自动跟随只应作为**低速、受控场景功能**开发和演示，不应把普通人体检测等同于完整自主导航。

## 8. 与 PetStateMachine 的关系

`AutoFollowState` 不放进高层交互状态机。

AppController 可以根据产品状态决定：

```text
Emergency → disable follow
Sleep     → disable follow
Manual control active → suspend follow
```

但 `Following` 本身是运动子系统状态。

## 9. 性能

AutoFollowController 应是轻量几何/规则控制，不做额外神经网络推理。

视觉模型由 PerceptionService 负责，控制器只消费最新语义观测。

## 10. 引入版本

基础小车控制稳定、MCU watchdog 和 stop 链路验证完成之后再引入。