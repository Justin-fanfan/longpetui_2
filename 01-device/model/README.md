# Model / DTO

[← 宠物本体](../README.md)

Model 是普通 C++ 数据结构，用于跨层传递业务数据。默认不继承 QObject，不持有线程、文件、Widget、数据库连接或网络连接。

推荐模型：

- [ReminderModels](ReminderModels.md)
- [PerceptionModels](PerceptionModels.md)
- [SpeechModels](SpeechModels.md)
- [MotionModels](MotionModels.md)
- [DeviceAndFamilyModels](DeviceAndFamilyModels.md)

原则：Model 描述“数据是什么”，Service 描述“数据怎样产生/变化”。

运动相关尤其要保持边界：视觉 Model 可以描述目标位置/置信度，Motion Model 可以描述受限运动意图，但都不携带 PWM、串口对象或电机寄存器。