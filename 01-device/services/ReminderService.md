# ReminderService

[← Services](README.md)

## 职责

- Reminder CRUD；
- enable/disable；
- 重复规则；
- 计算下一次触发；
- 管理一次 Reminder occurrence 的 `Pending / Presented / Acknowledged / Completed / Missed` 生命周期；
- 未确认时按有界策略重新展示；
- 写 ReminderRepository；
- 发出语义化提醒事件。

ReminderService 负责“提醒业务规则”，但不负责页面、TTS、音频播放或 Family 协议。

## 推荐接口

```cpp
QList<Reminder> reminders() const;
Result add(const ReminderDraft&);
Result update(ReminderId, const ReminderDraft&);
Result remove(ReminderId);

Result acknowledge(ReminderId, ReminderAckSource source);
Result markCompleted(ReminderId);

signals:
    void remindersChanged();
    void reminderTriggered(Reminder reminder);
    void reminderPresentationRequested(Reminder reminder);
```

实际实现可以将 occurrence id 一并带入 acknowledge/complete 接口，以避免同一 Reminder 在跨天或多次 occurrence 中产生歧义。

## 调度方式

不要“一条 Reminder 一个永久 QTimer”。

推荐继续使用：

```text
查询有效提醒
→ 计算最近 next_due
→ 单个 timer 等待
→ 创建/恢复 occurrence
→ 请求展示
→ 重新计算下一条
```

系统时间变化后重新计算。

## 主动提醒与重复展示

“提醒已投递”不能等价于“用户已确认”。

推荐流程：

```text
到达计划时间
→ occurrence = Pending
→ reminderPresentationRequested
→ occurrence = Presented
→ 等待用户确认
```

若在本次展示窗口内没有确认：

```text
Presented
→ 等待 repeatIntervalMinutes
→ 若 presentationCount < maxRepeatCount
→ 再次 reminderPresentationRequested
```

重复次数必须有上限，不能无限抢占 UI 或无限播放语音。具体默认间隔、最大次数属于产品配置，可由后续版本调整。

当用户确认后：

```text
Touch / Voice
→ acknowledge(...)
→ occurrence = Acknowledged
→ 停止该 occurrence 后续重复展示
```

如果用户明确表示“已经完成”，例如“已经吃药了”，再进入 `Completed`。`Acknowledged` 与 `Completed` 不应混用。

## 与 ReminderAlertPage

ReminderPage 是管理页面；到点后不应该把用户导航到提醒列表。

ReminderService 只发业务事件：

```text
reminderPresentationRequested
```

由 AppController 决定：

- 记录/恢复提醒前页面；
- 进入 `ReminderAlertPage`；
- 请求 Audio/TTS 能力进行播报；
- 用户确认后恢复原页面或展示下一条到期提醒。

## 与家属端

家属修改 Reminder 最终也必须进入 ReminderService，这样本地 UI 和 Electron 共享一套校验与业务规则。

家属端可以配置：

- `displayText`；
- `iconKey`；
- TTS 文本或家属录音 asset；
- 重复间隔与最大重复次数；
- 时间、日期、重复规则与启用状态。

跨设备同步使用稳定 `uuid`；本地数据库自增 id 不应作为 Family 协议的长期标识。

## 不负责

- 页面布局；
- TTS 引擎；
- 音频解码和扬声器；
- Robot 动作；
- Family 协议；
- KWS 模型实现。

## 引入版本

V0.2 引入 Reminder CRUD/调度；主动展示、确认与重复投递模型建议作为 V0.2 上机适配增量落地，语音关键词确认在 KWS 接入后启用。