# Model / DTO

[← 宠物本体](../README.md)

Model 是普通 C++ 数据结构，用于跨层传递业务数据。默认不继承 QObject，不持有线程、文件、Widget 或网络连接。

推荐模型：

- [ReminderModels](ReminderModels.md)
- [PerceptionModels](PerceptionModels.md)
- [SpeechModels](SpeechModels.md)
- [DeviceAndFamilyModels](DeviceAndFamilyModels.md)

原则：Model 描述“数据是什么”，Service 描述“数据怎样产生/变化”。