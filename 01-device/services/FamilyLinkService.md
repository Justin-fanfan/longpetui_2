# FamilyLinkService

[← Services](README.md)

## 1. 定位

宠物侧家属端业务网关。

Electron 应用看到的是“经过业务筛选的宠物能力”，不是 SQLite、UART 或设备底层 API。

## 2. 可提供的查询

建议：

- DeviceSummary；
- CareSummary；
- Reminder 列表、稳定 uuid 与 occurrence 状态；
- Reminder 的 `Acknowledged / Completed / Missed` 状态与最近处理时间；
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

`reminder.upsert` 可以承载家属端允许配置的 Reminder 业务字段，例如：

```text
uuid
displayText
iconKey
voiceType
voiceText
voiceAssetId
timeOfDay
scheduledDate
repeatRule
repeatIntervalMinutes
maxRepeatCount
enabled
revision
```

Family 协议不应发送终端本地绝对文件路径。自定义录音、图片等资源必须通过受控 asset id、下载校验和本地缓存管理。

默认命令白名单**不包含实时底盘驾驶**。

## 4. Reminder 同步原则

家属端与老人端不是两套 Reminder 逻辑：

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

跨设备身份使用 Reminder `uuid`；SQLite 自增 id 仅作为设备本地实现细节。

家属端可以自定义提醒文字、内置图标、TTS 文本或录音资源，但最终都必须进入 ReminderService 做字段校验、revision 校验和调度重算。

## 5. Reminder 状态回传

建议区分：

```text
Presented     // 已展示给老人
Acknowledged  // 老人已看到/听到并确认
Completed     // 老人明确表示任务已完成
Missed        // occurrence 最终未完成/未确认，具体规则由产品定义
```

不要把“老人点了一下屏幕”直接上报成“已经服药”。这样 Family App 才能给家属显示有业务意义的状态。

提醒状态变化属于适合推送的低频重要事件，例如：

```text
reminder acknowledged
reminder completed
reminder missed
```

## 6. 禁止直接开放

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

## 7. 与 MotionService

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

## 8. 推送策略

只在重要状态变化时推送。不要把每帧人体检测、每次 AutoFollow steering 更新、每 100ms 工程指标发给 Electron。

适合推送：

```text
reminder acknowledged/completed/missed
motion fault changed
motion became unavailable
important mode change
```

## 9. 引入版本

家属端联调时，建议 V0.5。Reminder 模型中的 uuid、内容、图标和语音字段可以提前在本地版本预留，避免 V0.5 再迁移一套业务模型。