# Platform / Adapter

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

这一层隔离 Linux、龙芯硬件和第三方库 API。

- [AlsaAudioDevice](AlsaAudioDevice.md)
- [CameraCapture](CameraCapture.md)
- [LocalInference](LocalInference.md)
- [UartRobotDriver](UartRobotDriver.md)
- [PythonWorkerOption](PythonWorkerOption.md)

上层 Service 应看到稳定语义，不应散落 `/dev/*`、ALSA、ORT、sherpa 或串口细节。