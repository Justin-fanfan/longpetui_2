# Device / Family DTO

[← Model](README.md)

## DeviceSummary

给家属端/设置页使用的经过筛选摘要：

```text
deviceId
online/uptime
softwareVersion
battery/power
storageSummary
aiServerReady
motionAvailable
motionFaultSummary
isMoving（可选，只表示状态）
lastUpdated
```

不要把整个 AppState、MCU 原始寄存器、PWM、完整 telemetry 或 `/proc` 原始文本发给 Electron。

运动状态只提供必要摘要，例如：

```text
motionAvailable = true/false
motionFaultSummary = none / timeout / motor_fault / ...
isMoving = true/false
```

这不意味着 Family App 获得运动控制权限。

## FamilyCommand

解析后的白名单命令：

```text
commandType
requestId
payload
senderIdentity
```

进入业务 Service 前还需权限和字段校验。

默认 Family command 白名单不包含：

```text
raw UART
PWM
wheel speed register
realtime drive
```

如果未来真正增加远程驾驶，应定义独立 DTO、权限、lease 和安全协议，不能把普通 FamilyCommand 任意扩展成电机控制。

## CommandResult

```text
requestId
success
errorCode
message
newRevision（如适用）
```

## PairingRecord

只保存必要的配对身份/凭证元数据。敏感 secret 的存储方式由 Security 文档约束。