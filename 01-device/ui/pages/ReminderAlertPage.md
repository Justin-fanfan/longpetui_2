# ReminderAlertPage

[← Pages](README.md)

## 1. 定位

`ReminderAlertPage` 是 Reminder 到期时主动抢占显示的**适老提醒投递页**。

它和 `ReminderPage` 的职责不同：

- `ReminderPage`：用户主动进入，用于管理提醒；
- `ReminderAlertPage`：系统主动进入，用于让老人看见、听见并确认当前提醒。

## 2. 适老显示原则

1024×600 终端优先一次展示 **1 条 Reminder**；同一时刻多条到期时，按队列逐条确认后展示下一条。

产品确有需要时最多同时展示 2 条，不应把 Reminder 管理列表直接搬到主动提醒页。

单条提醒建议包含：

```text
大图标
大字号 displayText
计划时间
一个主要确认动作
简短语音提示，例如“也可以说：知道了”
```

触控目标必须足够大，避免小字号状态标签、复杂列表、滚动和多层编辑操作。

## 3. 推荐 API

```cpp
void setReminder(const Reminder& reminder);

signals:
    void acknowledgeRequested(ReminderId id); // 看到了/知道了
    void completeRequested(ReminderId id);    // 明确已经完成，可按产品需要提供
```

如果业务层使用 occurrence id，应优先让 signal 携带 occurrence id，而不是仅靠 ReminderId。

## 4. 确认语义

默认的大按钮或整屏确认动作只表示：

> 用户已经看到/听到这条提醒。

因此触摸确认进入 `Acknowledged`，不能自动进入 `Completed`。

对于“已经吃药了”等明确完成动作，可以单独提供完成按钮或语音关键词，再进入 `Completed`。

## 5. 语音确认

在 `ReminderAlertPage` 可见期间，AppController 可以将本地 KWS 语义映射为：

```text
“知道了” / “好的”
→ acknowledgeRequested
```

```text
“完成了” / “吃过了”
→ completeRequested
```

关键词确认必须带当前 UI/Attention 上下文；普通待机或聊天状态下听到“知道了”不能误确认 Reminder。

完整 ASR 和远端 AI 不是提醒确认的前置条件。

## 6. 页面抢占与恢复

AppController 在进入 ReminderAlertPage 前记录可恢复的前一页面：

```text
Settings / Care / Home / Companion
        ↓ Reminder 到期
ReminderAlertPage
        ↓ 确认
恢复前一页面
```

若还有排队的到期 Reminder，则先展示下一条，再恢复原页面。

Emergency 优先级高于 ReminderAlert。紧急状态发生时允许中断普通提醒展示，Reminder occurrence 保持未确认并由 ReminderService 后续重新安排。

## 7. 语音/图标降级

页面只消费业务模型中的 `displayText` 与 `iconKey`，不直接访问 Family 下载目录或网络。

语音播放由 AppController 协调 Audio/TTS 能力：

```text
家属录音可用 → 播放录音
失败 → voiceText TTS
仍不可用 → 提示音 + 页面大字
```

即使离线或音频能力失败，屏幕提醒仍必须可用。

## 8. 不负责

- Reminder 调度；
- 重复提醒次数；
- SQLite；
- Family 协议；
- TTS/音频引擎；
- KWS 模型。

## 9. 引入版本

建议作为 V0.2 上机适配增量引入；语音关键词确认在 V0.3 KWS 能力接入后启用。