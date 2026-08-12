# 家属端同步

[← Flows](README.md)

## 查看状态

```text
Electron request / subscribe
 ↓
FamilyGateway
 ↓
FamilyLinkService
 ├── CareService
 ├── ReminderService
 ├── SettingsService
 └── SystemService
 ↓
sanitized DTO
 ↓
Electron
```

## 修改设置

```text
Electron settings.update
 ↓ authenticated request
FamilyLinkService
 ↓ validate whitelist
SettingsService
 ↓
Repository / Platform
 ↓
CommandResult(requestId)
```

## 推送

仅在重要变化时推：

```text
Reminder changed
CareSummary changed
Device online/offline state
AI server capability change（若家属需要看到）
```

不要推每帧检测或高频 CPU 指标。

## 冲突

资源 revision 不匹配时返回 conflict；Electron 重新拉最新数据再提示用户。