# UartRobotDriver

[← Platform](README.md)

## 定位

隔离实体宠物底层控制协议。

## 负责

- UART open/config；
- packet framing；
- command id；
- checksum/CRC；
- response/ACK；
- timeout；
- driver error；
- stop/emergency command。

如某些执行器使用 GPIO/PWM，可增加对应小型 driver。

## 上层 API

RobotService 不应看到字节协议。

```text
RobotService::nod()
    ↓
UartRobotDriver::send(HeadNodCommand)
```

## 可靠性

- 所有运动命令应有超时；
- 失联后进入安全停止状态；
- Emergency stop 命令优先；
- 不要把长动作序列全部塞入 Driver。

长动作由 RobotService/PetBehaviorController 编排。