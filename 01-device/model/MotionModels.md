# Motion Models

[← Model / DTO](README.md)

## 1. 定位

运动模块相关的数据模型只描述“运动意图、运动状态和 MCU 回传信息是什么”，不执行控制算法，也不持有串口、线程或视觉模型。

## 2. MotionIntent

龙芯板向运动服务表达的高层运动意图。推荐使用带单位、带限制的字段，而不是直接传 PWM。

```cpp
struct MotionIntent
{
    float linearVelocity;   // 前后速度，单位由协议统一，例如 m/s
    float angularVelocity;  // 转向角速度，例如 rad/s
    MotionSource source;
};
```

如果第一版 MCU 协议只支持离散命令，也可以先使用：

```text
Stop
ForwardSlow
BackwardSlow
TurnLeft
TurnRight
```

但上层仍应叫“MotionIntent”，不要把电机寄存器或 PWM 暴露给视觉/业务代码。

## 3. MotionSource

推荐至少区分：

```text
Idle
UserLocal
PetBehavior
AutoFollow
Emergency
```

用于控制权仲裁和日志追踪。

## 4. MotionTelemetry

MCU 回传的运行状态可整理为：

```text
isMoving
left/right wheel speed（若可得）
current motion mode
fault code
watchdog state
obstacle/safety sensor state（若硬件具备）
last command sequence
```

## 5. AutoFollowState

视觉自动跟随内部状态建议独立：

```text
Disabled
AcquiringTarget
Following
TargetLost
SafetyStopped
```

这些不是 `PetStateMachine` 的主交互状态。

## 6. 原则

- Model 不保存摄像头帧；
- 不保存串口对象；
- 不允许视觉输出直接携带 PWM；
- 协议单位必须在宠物端与 MCU 固件之间明确并版本化。

## 7. 引入版本

运动底盘正式接入时引入；自动跟随后扩展 `AutoFollowState` 即可。