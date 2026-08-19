# Reminder / Care 数据流

[← Flows](README.md)

## 新建/编辑

```text
ReminderEditPage / Family App
 ↓ ReminderDraft / reminder.upsert
AppController / FamilyLinkService
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

本地 UI 和家属端必须共享同一 ReminderService 校验与调度逻辑，不另写一套“远程提醒”。

## 到期与主动展示

Reminder 到期后不进入 Reminder 管理列表，也不能只显示 Toast。

```text
single next-due scheduler
 ↓
ReminderService creates/resumes occurrence
 ↓
reminderPresentationRequested
 ↓
AppController
 ├── save previous restorable page
 ├── AttentionState = Reminder
 ├── ReminderAlertPage
 └── optional Audio/TTS playback
```

ReminderAlertPage 默认一次展示 1 条大字 + 大图标提醒；同一时刻多条到期时按队列逐条处理，产品确有需要时最多同时展示 2 条。

## 确认

触摸确认：

```text
ReminderAlertPage
 ↓ acknowledgeRequested
AppController
 ↓
ReminderService.acknowledge(source = Touch)
 ↓
ReminderEvent = Acknowledged
```

语音确认：

```text
KeywordSpottingService
 ↓ ReminderAcknowledge
AppController checks Reminder context
 ↓
ReminderService.acknowledge(source = Voice)
 ↓
ReminderEvent = Acknowledged
```

Reminder 语音确认不依赖完整 ASR 或远端 AI。

## 未确认重复展示

```text
Presented
 ↓ no acknowledgement during presentation window
ReminderService waits repeatIntervalMinutes
 ↓
presentationCount < maxRepeatCount ?
 ├── yes → reminderPresentationRequested again
 └── no  → stop re-presenting and apply product Missed policy
```

重复策略必须有界，不能无限抢占 UI 或无限播放语音。

## Acknowledged 与 Completed

```text
“知道了” / 点击确认
→ Acknowledged
```

```text
“已经吃药了” / 明确完成按钮
→ Completed
```

两者不能混用。CareService 的“用药完成”统计应依据 `Completed`，不能因为老人只是关闭提醒就记为已服药。

## 页面恢复

```text
Settings / Care / Home / Companion
        ↓ Reminder 到期
ReminderAlertPage
        ↓ acknowledge / complete
若有下一条到期 Reminder → 继续展示
否则 → restore previous page
```

Emergency 优先级高于 ReminderAlert；Emergency 抢占后 occurrence 仍保持未确认，由 ReminderService 后续重新安排。

## 语音/图标降级

```text
voiceAssetId 可用 → 播放家属录音
        ↓ 失败
voiceText 可用 → TTS
        ↓ 不可用
提示音 + ReminderAlertPage 大字
```

屏幕提醒与触摸确认必须保持完全本地可用。

## 家属修改

```text
Family App
 ↓ reminder.upsert(uuid, displayText, iconKey, voice..., schedule...)
FamilyGateway
 ↓
FamilyLinkService
 ↓
ReminderService
 ↓
Repository / SQLite
```

Family App 可以配置提醒内容、图标、语音和重复策略，但不绕过 ReminderService，也不向终端同步任意文件路径。