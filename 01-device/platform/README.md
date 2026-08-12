# Platform / Adapter

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

这一层隔离 Linux、龙芯硬件、MCU 边界和第三方库 API。

- [AlsaAudioDevice](AlsaAudioDevice.md)
- [CameraCapture](CameraCapture.md)
- [LocalInference](LocalInference.md)
- [UartRobotDriver](UartRobotDriver.md)
- [运动 MCU 边界](MotionMcuBoundary.md)
- [PythonWorkerOption](PythonWorkerOption.md)

上层 Service 应看到稳定语义，不应散落 `/dev/*`、ALSA、ORT、sherpa、串口或电机协议细节。

## 运动相关边界

小车底盘由 MCU 直接控制，龙芯板只做高层间接控制：

```text
MotionService
    ↓
UartRobotDriver / MCU protocol adapter
    ↓
Motion MCU
    ↓
Motor Driver / Chassis
```

实时 PWM、轮速闭环、watchdog 和失联停车应尽量留在 MCU 一侧。