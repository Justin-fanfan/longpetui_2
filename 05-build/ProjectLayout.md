# 长期源码目录

[← Build](README.md)

## 推荐终局方向

```text
LongPet/
├── CMakeLists.txt
├── cmake/toolchains/
├── src/
│   ├── main.cpp
│   ├── app/
│   │   ├── Application.*
│   │   ├── AppController.*
│   │   ├── AppState.*
│   │   ├── PetStateMachine.*
│   │   ├── PetBehaviorController.*
│   │   └── AiCapabilityPolicy.*
│   ├── ui/
│   │   ├── MainWindow.*
│   │   ├── pages/
│   │   └── widgets/
│   ├── model/
│   │   └── MotionModels.*
│   ├── services/
│   │   ├── MotionService.*
│   │   └── ...
│   ├── data/
│   ├── platform/
│   │   ├── audio/
│   │   ├── camera/
│   │   ├── inference/
│   │   ├── robot/
│   │   └── motion/       # MCU protocol / chassis adapter，实际规模够大后再单独建
│   ├── connectivity/
│   └── features/
│       ├── CreativeFeatureCoordinator.*
│       └── AutoFollowController.*
├── resources/
├── config/
├── tools/
└── docs/
```

## 运动代码的建议落点

逻辑职责比“物理上是不是同一个 MCU”更重要：

```text
services/MotionService
→ 底盘业务安全、owner、限速

features/AutoFollowController
→ 视觉观测到 MotionIntent

platform/robot or platform/motion
→ MCU/UART 协议
```

如果第一版只有一个 `UartRobotDriver.*`，不必立刻建立 `platform/motion/` 目录；等底盘协议代码明显增多再拆。

## V0.1 实际目录

不要直接创建上面所有空目录。

V0.1 只需：

```text
src/
├── main.cpp
├── MainWindow.*
├── pages/
│   ├── CompanionPage.*
│   └── HomePage.*
└── widgets/
    ├── PetFaceWidget.*
    ├── VisualComponents.*
    └── VisualTokens.h
resources/
cmake/toolchains/
```

## V0.2

引入：

```text
app/
model/
data/
services/
```

## V0.3/V0.4

再根据真实能力引入：

```text
platform/
connectivity/
features/
```

运动底盘建议先建立 `MotionService + 当前实际 MCU Driver`，自动跟随后再加入 `AutoFollowController`。

## 命名

- Page：`XxxPage`；
- Service：`XxxService`；
- 高层控制器：`XxxController`，如 `AutoFollowController`；
- 硬件/库 Adapter：具体实现名，如 `AlsaAudioInput`、`OrtVisionEngine`、`UartRobotDriver`；
- 数据访问：`XxxRepository`；
- DTO/Model：业务名，不加 Manager。

尽量少用含义模糊的 `Manager`。