# PetBehaviorController

[← Application 模块](README.md)

## 1. 定位

将“产品状态”转换成“宠物的视觉与实体表现”。

它解决一个核心问题：

> 屏幕上的宠物脸和实体机器宠物动作应该像同一个角色，而不是两个独立系统。

## 2. 输入

主要订阅：

```text
PetStateMachine::stateChanged
```

并可读取少量上下文，例如是否检测到用户在前方、MotionService 当前是否允许移动。

## 3. 输出

### UI 表现

```text
Companion → DefaultOpen
Listening → Listening
Thinking → Thinking
Speaking → Speaking
Sleep → Sleep
Emergency → Alert
```

### 非底盘实体行为

通过 `RobotService`：

```text
Companion → idle pose
Human detected → lookAtUser
Listening → face user / calm pose
Speaking → optional low-frequency expression movement
Emergency → alertPose
```

### 底盘行为

底盘移动必须通过 `MotionService`，而且默认只在明确产品功能需要时使用。

例如：

```text
自动跟随
→ AutoFollowController
→ MotionService
```

`Speaking`、`Happy`、`Playful` 等表情状态**不应自动等价于小车前进/转向**。

## 4. 依赖

```text
PetStateMachine
    ↓
PetBehaviorController
   ├── MainWindow/Page presentation API
   ├── RobotService
   └── MotionService（仅高层允许/停止等有限调用）
```

视觉闭环本身由 `AutoFollowController` 处理，不放到 PetBehaviorController。

## 5. Emergency

Emergency 到达时应优先：

```text
MotionService.forceStop / stop(Emergency)
RobotService stop/cancel normal action
PetFace → Alert
```

运动停止不能等待表情动画或远端服务完成。

## 6. 不负责

- 判断状态应该何时发生；
- 自动跟随控制算法；
- UART packet；
- QPainter 图形；
- 摄像头推理；
- 语言模型。

## 7. 设计建议

行为应保持低频、可中断。不要把一次 Speaking 设计成一个长达数秒、无法取消的机械动作序列。

底盘运动和普通角色动作应使用不同安全边界；Emergency 等高优先级状态必须可以立即停止两者。

## 8. 引入版本

机器人动作开始实际接入时，建议 V0.3/V0.4。