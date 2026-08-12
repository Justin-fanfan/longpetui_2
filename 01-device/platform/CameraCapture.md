# CameraCapture / V4L2Camera

[← Platform](README.md)

## 职责

- 打开 camera device；
- format negotiation；
- buffer management；
- frame timestamp；
- 输出最新帧；
- 设备断开/错误恢复。

## 数据模型

推荐“latest frame”而非无界队列：

```text
Camera thread
→ update latest frame
→ PerceptionService 按 2～5 FPS 取
```

这样视觉推理变慢时不会积压数秒旧画面。

## 不负责

- person detection；
- gesture classification；
- UI preview；
- Family camera streaming。

## OpenCV

若算法使用 OpenCV，可在 adapter/service 边界将帧转换为统一 image view，避免页面和其他模块都依赖 cv::Mat。