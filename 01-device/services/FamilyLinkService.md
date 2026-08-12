# FamilyLinkService

[← Services](README.md)

## 1. 定位

宠物侧家属端业务网关。

Electron 应用看到的是“经过业务筛选的宠物能力”，不是 SQLite、UART 或设备底层 API。

## 2. 可提供的查询

建议：

- DeviceSummary；
- CareSummary；
- Reminder 列表/完成状态；
- 配对/连接状态；
- 允许的 Settings；
- 最近同步时间；
- 可选运动模块健康摘要：MCU online/fault/是否正在移动。

运动状态只作为摘要，不返回原始 PWM/寄存器/高频轮速流。

## 3. 可接受的命令

白名单化，例如：

```text
reminder.upsert
reminder.delete
settings.update
family.contact.update
```

最终仍调用对应 Service。

默认命令白名单**不包含实时底盘驾驶**。

## 4. 例子

```text
Electron reminder.upsert
        ↓
FamilyGateway
        ↓
FamilyLinkService
        ↓
ReminderService
        ↓
Repository/SQLite
        ↓
command.result
```

## 5. 禁止直接开放

```text
SQL
shell
file browser
UART/GPIO
motor PWM
wheel register
realtime chassis drive
raw camera stream
raw microphone stream
```

若未来确实需要远程音视频或远程驾驶，必须作为独立安全功能设计。

## 6. 与 MotionService

当前 FamilyLinkService 可以读取经过筛选的 Motion/Device 健康摘要，但不拥有 MotionService 的实时 owner。

未来若产品真的加入远程驾驶，调用链也必须是：

```text
FamilyGateway
→ FamilyLinkService
→ dedicated validated remote-motion feature
→ MotionService
→ MCU
```

而不能：

```text
FamilyGateway → UartRobotDriver
```

## 7. 推送策略

只在重要状态变化时推送。不要把每帧人体检测、每次 AutoFollow steering 更新、每 100ms 工程指标发给 Electron。

适合推送：

```text
motion fault changed
motion became unavailable
important mode change
```

## 8. 引入版本

家属端联调时，建议 V0.5。