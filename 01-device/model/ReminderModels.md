# Reminder / Care Models

[← Model](README.md)

## Reminder

Reminder 是本地 UI 与家属端共享的业务定义，不把“页面显示内容”“远端同步字段”和“调度字段”拆成多套模型。

建议字段：

```text
ReminderId id
QString uuid                // 跨设备稳定标识，本地数据库 id 仍仅用于本机
ReminderType type
QString displayText         // 老人端实际显示的大字提醒内容
QString iconKey             // 内置图标 key；未来可扩展 custom asset id
ReminderVoiceType voiceType // None / Tts / AudioAsset
QString voiceText           // TTS 文本与录音失败时的 fallback 文本
QString voiceAssetId        // 家属录音等同步资产标识，不保存远端文件路径
timeOfDay
scheduledDate
repeatRule
int repeatIntervalMinutes
int maxRepeatCount
enabled
revision
createdAt
updatedAt
```

`uuid` 用于 Family App ↔ LongPet 同步；SQLite 自增 `id` 继续作为本地 Repository 主键。

`iconKey` 第一阶段优先使用终端内置图标，保证离线时可显示。若未来允许家属上传自定义图片，应通过受控 asset id / cache 管理，不把任意文件路径写进 Reminder。

## ReminderDraft

页面编辑或家属端 upsert 时使用，允许尚未拥有数据库 id。保存前统一进入 ReminderService 校验。

本地 ReminderEditPage 可以只暴露当前版本支持的字段；家属端可以提供更完整的内容、图标、语音和重复策略配置，但最终仍映射到同一个 ReminderDraft/Reminder 业务模型。

## ReminderEvent

Reminder 定义“什么时候提醒、提醒什么”；ReminderEvent 描述某一次实际 occurrence 的生命周期。

建议字段：

```text
reminderId
scheduledAt
status              // Pending / Presented / Acknowledged / Completed / Missed
presentationCount
lastPresentedAt
acknowledgedAt
ackSource            // Touch / Voice / Family / None
completedAt
```

必须区分：

- `Acknowledged`：用户已看到/听到并确认提醒；
- `Completed`：用户明确表示任务已经完成，例如已经服药。

因此“轻触屏幕关闭提醒”不能自动等价为“已经服药”。

## 提醒语音

建议：

```text
ReminderVoiceType::None
ReminderVoiceType::Tts
ReminderVoiceType::AudioAsset
```

播放策略应支持降级：

```text
AudioAsset 可用 → 播放家属录音
        ↓ 失败
voiceText 可用 → TTS
        ↓ 不可用
提示音 + 屏幕大字
```

ReminderService 只保存/调度这些业务字段，不负责具体 TTS、音频解码或扬声器播放。

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

Care 的“用药完成”应依赖明确的 `Completed`，而不是仅依赖 `Acknowledged`，这样 CarePage 与 Electron 使用同一业务口径。