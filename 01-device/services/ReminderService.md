# ReminderService

[← Services](README.md)

## 职责

- Reminder CRUD；
- enable/disable；
- 重复规则；
- 计算下一次触发；
- Completed/Pending/Missed；
- 写 ReminderRepository；
- 发出 `reminderTriggered`。

## 推荐接口

```cpp
QList<Reminder> reminders() const;
Result add(const ReminderDraft&);
Result update(ReminderId, const ReminderDraft&);
Result remove(ReminderId);
void markCompleted(ReminderId);

signals:
    void remindersChanged();
    void reminderTriggered(Reminder reminder);
```

## 调度方式

不要“一条 Reminder 一个永久 QTimer”。

推荐：

```text
查询有效提醒
→ 计算最近 next_due
→ 单个 timer 等待
→ 触发
→ 重新计算下一条
```

系统时间变化后重新计算。

## 与家属端

家属修改 Reminder 最终也必须进入 ReminderService，这样本地 UI 和 Electron 共享一套校验与业务规则。

## 不负责

- 页面；
- TTS；
- Robot 动作；
- Family 协议。

## 引入版本

V0.2。