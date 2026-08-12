# FamilyLinkService

[← Services](README.md)

## 1. 定位

宠物侧家属端业务网关。

Electron 应用看到的是“经过业务筛选的宠物能力”，不是 SQLite 或设备底层 API。

## 2. 可提供的查询

建议：

- DeviceSummary；
- CareSummary；
- Reminder 列表/完成状态；
- 配对/连接状态；
- 允许的 Settings；
- 最近同步时间。

## 3. 可接受的命令

白名单化，例如：

```text
reminder.upsert
reminder.delete
settings.update
family.contact.update
```

最终仍调用对应 Service。

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
raw camera stream
raw microphone stream
```

若未来确实需要远程音视频，必须作为独立安全功能设计。

## 6. 推送策略

只在重要状态变化时推送。不要把每帧人体检测或每 100ms 工程指标发给 Electron。

## 7. 引入版本

家属端联调时，建议 V0.5。