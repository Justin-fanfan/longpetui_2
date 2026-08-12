# 运动 MCU 边界

[← Platform](README.md)

## 1. 硬件控制关系

LongPet 小车运动模块由单片机直接控制，龙芯 2K0300 板间接控制。

推荐明确分工：

```text
龙芯 2K0300
负责：视觉、产品状态、自动跟随决策、高层运动目标
        ↓
通信协议（当前实际硬件可为 UART/串口等）
        ↓
运动 MCU
负责：实时电机控制、PWM/方向、轮速闭环、watchdog、安全停机
        ↓
Motor Driver
        ↓
Wheels / Chassis
```

## 2. 为什么实时底层控制必须留在 MCU

Linux/Qt 用户态不适合承担严格实时的电机 PWM/闭环。

龙芯板可能同时运行 UI、视觉、KWS、SQLite 和网络，因此调度延迟会波动。MCU 应成为底盘实时执行与最后一道失联停车保护。

## 3. 龙芯板应该发送什么

优先发送高层、受约束目标，例如：

```text
STOP
SET_VELOCITY(linear, angular)
MOVE_SLOW(direction)
SET_MOTION_ENABLE
HEARTBEAT / LEASE
```

具体协议取决于 MCU 固件能力。

不推荐龙芯视觉模块直接发送：

```text
left_pwm = 83%
right_pwm = 47%
```

除非 MCU 本身只是最薄的电机桥且项目经过专门实时/安全设计；默认架构不采用这种方式。

## 4. MCU 应独立承担的安全能力

至少建议：

- command/heartbeat watchdog；
- 通信超时自动停车；
- 无效命令拒绝；
- 最大 PWM/速度限制；
- motor fault 处理；
- reset 后默认禁止运动；
- Emergency/Stop 命令高优先级。

若硬件有障碍/碰撞传感器，越接近电机执行层的硬安全判断越不应依赖 Linux 正常运行。

## 5. Telemetry

MCU 可周期回传：

```text
firmware/protocol version
motion enabled
current velocity / wheel speed
fault flags
watchdog state
battery/motor voltage（若有）
obstacle/safety flags（若有）
last accepted command sequence
```

龙芯侧由 Driver 解析，再交给 MotionService。

## 6. 协议建议

每条运动命令建议包含：

```text
protocol version
command type
sequence
payload length
payload
checksum/CRC
```

涉及持续运动时，应采用“续租/heartbeat”思想：旧命令不能无限期有效。

## 7. 与 UartRobotDriver 的关系

如果龙芯与 MCU 当前通过 UART：

```text
MotionService
   ↓
UartRobotDriver
   ↓
Motion MCU
```

`UartRobotDriver` 负责字节协议、ACK、timeout；MCU 固件负责真正电机控制。

如果未来链路换成其他总线，MotionService 不应因此重写。

## 8. 测试底线

在做自动跟随前，先单独验证：

1. 龙芯进程退出 → MCU 自动停车；
2. 串口拔掉/通信断开 → MCU 自动停车；
3. command 卡住 → watchdog 自动停车；
4. Emergency stop 可立即覆盖普通移动；
5. MCU reset 后不会自行恢复旧运动。

这些通过后，再把视觉闭环接上。