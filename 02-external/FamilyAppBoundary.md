# 家属 Electron 应用边界

[← 外部系统](README.md)

## 1. 家属端定位

Electron 应用是 LongPet 的：

```text
查看
配置
远程关怀
```

终端，不是远程 Shell/数据库工具。

## 2. 建议查看内容

- 宠物在线/最近同步；
- 基础 DeviceSummary；
- Reminder；
- Reminder 完成情况；
- CareSummary；
- 用户允许的设备设置；
- 配对状态。

## 3. 建议允许的修改

白名单化：

```text
新增/编辑/删除 Reminder
音量或部分用户设置
家属联系人
部分关怀配置
```

## 4. 正确调用链

例如编辑 Reminder：

```text
Electron
→ Family protocol
→ FamilyGateway
→ FamilyLinkService
→ ReminderService
→ ReminderRepository
→ SQLite
→ command result
```

而不是：

```text
Electron → SQLite table
```

## 5. 不应默认开放

- raw DB；
- shell；
- filesystem；
- UART/GPIO；
- 实时原始麦克风；
- 实时原始摄像头。

如果未来加入远程音视频，必须单独设计权限、用户提示和数据生命周期。

## 6. 连接拓扑

架构不强制：

```text
Electron 直连宠物 LAN endpoint
```

还是未来：

```text
Electron ↔ relay ↔ pet
```

上层 FamilyLinkService 只看业务 channel。

## 7. 多端冲突

本地老人和家属可能同时修改一条 Reminder。

建议资源拥有：

```text
revision / updatedAt
```

收到旧 revision 的更新时返回冲突，而不是无声覆盖。

## 8. 安全

Family App 必须先配对/鉴权。所有可执行命令均经过业务白名单和字段校验。