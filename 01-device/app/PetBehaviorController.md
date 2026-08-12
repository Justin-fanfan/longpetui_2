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

并可读取少量上下文，例如是否检测到用户在前方。

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

### 实体行为

```text
Companion → idle pose
Human detected → lookAtUser
Listening → face user / calm pose
Speaking → optional low-frequency movement
Emergency → alertPose
```

## 4. 依赖

```text
PetStateMachine
    ↓
PetBehaviorController
   ├── MainWindow/Page presentation API
   └── RobotService
```

## 5. 不负责

- 判断状态应该何时发生；
- UART packet；
- QPainter 图形；
- 摄像头推理；
- 语言模型。

## 6. 设计建议

行为应保持低频、可中断。不要把一次 Speaking 设计成一个长达数秒、无法取消的机械动作序列。

Emergency 等高优先级状态必须可以立即停止普通行为。

## 7. 引入版本

机器人动作开始实际接入时，建议 V0.3/V0.4。