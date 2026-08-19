# UI Pages

[← UI 模块](../README.md)

页面只负责两件事：

1. 把业务数据以适老方式显示出来；
2. 把用户操作转换成明确 signal。

页面不直接调用 ASR、TTS、SQLite、ONNX Runtime、网络或 UART。

Reminder 相关页面额外遵守：

- `ReminderPage` 是用户主动进入的提醒管理页；
- `ReminderAlertPage` 是 Reminder 到期时系统主动进入的高优先级适老提醒页；
- 到期提醒不能用 Reminder 管理列表或 Toast 代替正式投递。

页面文档：

- [CompanionPage](CompanionPage.md)
- [HomePage](HomePage.md)
- [ConversationPage](ConversationPage.md)
- [CarePage](CarePage.md)
- [ReminderPage](ReminderPage.md)
- [ReminderAlertPage](ReminderAlertPage.md)
- [ReminderEditPage](ReminderEditPage.md)
- [SettingsPage](SettingsPage.md)
- [EmergencyPage](EmergencyPage.md)
- [SleepPage](SleepPage.md)