# ReminderPage

[← Pages](README.md)

## 定位

ReminderPage 是**提醒管理页**，显示本地 Reminder 列表及视觉状态，供用户查看、新建、编辑和删除提醒。

它不是到点时主动抢占显示的提醒页面。到期提醒必须进入独立的 [ReminderAlertPage](ReminderAlertPage.md)。

## 推荐 API

```cpp
void setReminders(const QList<Reminder>& reminders);

signals:
    void backRequested();
    void addReminderRequested();
    void editReminderRequested(ReminderId id);
    void completeReminderRequested(ReminderId id); // 若产品仍保留手动完成入口
```

## 显示状态

```text
Pending
Presented / Acknowledged（可按产品需要简化显示）
Completed
Missed
Disabled
```

列表页主要承担“管理”和“历史/状态查看”，不承担当前提醒的高优先级交互。

## 与 ReminderAlertPage 的边界

```text
用户主动进入“提醒”
→ ReminderPage
→ 查看/编辑提醒
```

```text
Reminder 到期
→ ReminderService
→ AppController
→ ReminderAlertPage
```

不要在 Reminder 到期时自动跳到 ReminderPage，也不要用 Toast 代替正式提醒投递。

## 不负责

- SQL；
- QTimer 调度；
- 重复规则计算；
- 家属同步；
- 提醒语音播放；
- 未确认后的重复展示。

这些由 ReminderService、AppController 和对应音频能力协调完成。

## 引入版本

V0.2。