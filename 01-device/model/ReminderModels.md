# Reminder / Care Models

[← Model](README.md)

## Reminder

建议字段：

```text
ReminderId id
type
title
timeOfDay
repeatRule
enabled
revision
createdAt
updatedAt
```

## ReminderDraft

页面编辑时使用，允许尚未拥有数据库 id。保存前由 ReminderService 校验。

## ReminderEvent

描述一次实际计划触发：

```text
reminderId
scheduledAt
status
completedAt
```

## CareEvent

本地业务事件，例如喝水完成、一次有效互动。不要用它记录每帧视觉检测。

## CareSummary

UI/Family 共享的只读摘要：

```text
water
medicine
activity
interaction
lastUpdated
```

这样 CarePage 与 Electron 使用同一业务口径。