# ReminderPage

[← Pages](README.md)

## 定位

显示本地 Reminder 列表及视觉状态。

## 推荐 API

```cpp
void setReminders(const QList<Reminder>& reminders);

signals:
    void backRequested();
    void addReminderRequested();
    void editReminderRequested(ReminderId id);
```

## 显示状态

```text
Pending
Completed
Missed
Disabled（如产品需要）
```

## 不负责

- SQL；
- QTimer 调度；
- 重复规则计算；
- 家属同步。

这些由 ReminderService 完成。

## 引入版本

V0.2。