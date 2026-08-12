# Repositories

[← Data](README.md)

Repository 是业务 Service 与 SQLite 之间的数据访问边界。

## ReminderRepository

负责：

```text
Reminder CRUD
next due query
ReminderEvent
revision
```

## CareEventRepository

负责：

```text
CareEvent append
按时间范围查询
清理过旧数据
```

## SettingsRepository

负责用户产品设置。

## PairingRepository

当 Family/AI server 需要持久配对身份时保存必要记录。

## 不推荐

不要机械地为每一个 Repository 再创建：

```text
IReminderRepository
ReminderRepositoryImpl
SqliteReminderRepositoryFactory
```

当前只有一个 SQLite 实现时，具体类已经足够。只有真实存在第二实现或测试替身价值明显时再抽象接口。