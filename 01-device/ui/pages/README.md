# UI Pages

[← UI 模块](../README.md)

页面只负责两件事：

1. 把业务数据以适老方式显示出来；
2. 把用户操作转换成明确 signal。

页面不直接调用 ASR、TTS、SQLite、ONNX Runtime、网络或 UART。

页面文档：

- [CompanionPage](CompanionPage.md)
- [HomePage](HomePage.md)
- [ConversationPage](ConversationPage.md)
- [CarePage](CarePage.md)
- [ReminderPage](ReminderPage.md)
- [ReminderEditPage](ReminderEditPage.md)
- [SettingsPage](SettingsPage.md)
- [EmergencyPage](EmergencyPage.md)
- [SleepPage](SleepPage.md)