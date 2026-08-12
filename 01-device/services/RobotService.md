# RobotService

[← Services](README.md)

## 定位

向 Application 层暴露语义化的实体宠物动作。

## API 示例

```cpp
lookAtUser();
nod();
idleMotion();
alertPose();
stopMotion();
```

## 底层

```text
RobotService
    ↓
UartRobotDriver / GPIO / PWM adapter
```

Driver 处理协议；Service 处理高层动作语义。

## 可中断性

动作必须支持：

```text
Emergency
用户取消
模式切换
驱动错误
```

快速停止。

## 不负责

- 决定何时进入 Speaking；
- PetFace 绘制；
- UART packet 细节。

## 引入版本

实体执行机构接入时。