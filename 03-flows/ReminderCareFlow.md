# Reminder / Care 数据流

[← Flows](README.md)

## 新建/编辑

```text
ReminderEditPage
 ↓ saveRequested(ReminderDraft)
AppController
 ↓
ReminderService
 ↓ validate / calculate
ReminderRepository
 ↓
SQLite
 ↓
remindersChanged
 ↓
ReminderPage refresh
```

## 到期

```text
single next-due scheduler
 ↓
ReminderService::reminderTriggered
 ↓
AppController
 ↓
AttentionState = Reminder
 ↓
UI / optional TTS / optional Robot behavior
```

## 完成

```text
user completes
 ↓
ReminderService.markCompleted
 ↓
ReminderEvent saved
 ↓
CareService recompute summary
 ↓
CarePage / FamilyLinkService
```

## 家属修改

Electron 仍进入同一个 ReminderService，不另写一套远程 Reminder 逻辑。