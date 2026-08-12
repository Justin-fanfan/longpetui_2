# RobotService

[← Services](README.md)

## 1. 定位

`RobotService` 向 Application 层暴露**非底盘移动类**的实体宠物动作语义。

典型包括：

```text
lookAtUser
nod
idlePose
alertPose
stopExpressionMotion
```

它负责“宠物怎样做出姿态/角色动作”，不负责小车前进、后退、转向和自动跟随。

小车底盘统一由 [MotionService](MotionService.md) 管理。

## 2. 为什么和 MotionService 分开

普通角色动作与底盘移动的风险等级不同：

```text
点头 / 摆动
→ 局部执行器动作

前进 / 转向
→ 整机发生空间位移
```

底盘需要额外考虑：

- 速度限制；
- 控制权仲裁；
- 目标丢失停车；
- MCU heartbeat/watchdog；
- Emergency 强制停止；
- 自动跟随 enable/disable。

因此软件上建议拆开，即使最终硬件都由同一 MCU 执行。

## 3. 底层

```text
RobotService
    ↓
UartRobotDriver / GPIO / PWM adapter
```

Driver 处理协议；Service 处理高层动作语义。

## 4. 可中断性

角色动作必须支持：

```text
Emergency
用户取消
模式切换
驱动错误
```

快速停止。

不要把一次 Speaking 设计成数秒且无法取消的机械动作序列。

## 5. 与 PetBehaviorController

`PetBehaviorController` 可以同时调用：

```text
RobotService  → 角色动作
MotionService → 仅在产品策略允许时控制底盘
```

但默认 Speaking/Happy 等表情状态不应该自动意味着底盘移动。

## 6. 不负责

- 小车速度与转向；
- 自动跟随；
- 摄像头推理；
- PetFace 绘制；
- UART packet 细节。

## 7. 引入版本

非底盘实体执行机构接入时。