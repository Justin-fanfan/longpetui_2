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
│   ├── services/
│   ├── data/
│   ├── platform/
│   │   ├── audio/
│   │   ├── camera/
│   │   ├── inference/
│   │   └── robot/
│   ├── connectivity/
│   └── features/
├── resources/
├── config/
├── tools/
└── docs/
```

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

## 命名

- Page：`XxxPage`；
- Service：`XxxService`；
- 硬件/库 Adapter：具体实现名，如 `AlsaAudioInput`、`OrtVisionEngine`；
- 数据访问：`XxxRepository`；
- DTO/Model：业务名，不加 Manager。

尽量少用含义模糊的 `Manager`。