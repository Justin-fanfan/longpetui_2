# UartRobotDriver

[← Platform](README.md)

## 1. 定位

隔离龙芯板与实体宠物 MCU/执行机构之间的串口协议。

如果当前运动 MCU 使用 UART，则它位于：

```text
MotionService / RobotService
        ↓
UartRobotDriver
        ↓
Motion / Actuator MCU
```

`UartRobotDriver` 只负责通信与协议，不直接实现电机实时控制。

## 2. 负责

- UART open/config；
- packet framing；
- command id；
- checksum/CRC；
- response/ACK；
- timeout；
- driver error；
- sequence；
- stop/emergency command；
- motion telemetry decode；
- heartbeat/lease message（若协议采用）。

如某些执行器使用 GPIO/PWM，可增加对应小型 driver。

## 3. 上层 API

`RobotService` / `MotionService` 不应看到字节协议。

例如：

```text
MotionService::submitIntent(...)
    ↓
UartRobotDriver::sendMotionCommand(...)
```

或：

```text
RobotService::nod()
    ↓
UartRobotDriver::send(HeadNodCommand)
```

## 4. 与运动 MCU 的职责边界

龙芯侧 Driver 不负责：

- PWM 实时输出；
- 轮速闭环；
- 电机换向时序；
- 硬件级 watchdog；
- 最终失联停车。

这些应由运动 MCU 固件直接承担。

详见 [运动 MCU 边界](MotionMcuBoundary.md)。

## 5. 可靠性

- 所有运动命令应有时间语义或续租机制；
- 通信失联后龙芯侧立即上报不可用；
- MCU 侧 heartbeat/lease 超时必须自行停车；
- Emergency stop 命令优先；
- MCU reset 后不得自动恢复旧运动；
- 不把长动作序列全部塞入 Driver。

## 6. 长动作

长动作由：

```text
RobotService / PetBehaviorController
```

编排。

底盘的视觉自动跟随则由：

```text
AutoFollowController → MotionService
```

编排，Driver 只执行最后的受限命令。