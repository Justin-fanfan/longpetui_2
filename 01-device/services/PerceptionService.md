# PerceptionService

[← Services](README.md)

## 1. 定位

本体基础视觉感知统一入口：

- 人体/人员存在检测；
- 基础人体识别（按实际模型定义）；
- 手势识别；
- 后续必要的轻量安全感知。

## 2. 输入

来自 CameraCapture 的“最新帧”。

## 3. 输出

```cpp
signals:
    void humanPresenceChanged(bool present);
    void personObservationUpdated(PersonObservation);
    void gestureRecognized(GestureEvent);
```

## 4. Debounce

模型可能连续几十帧识别出同一挥手动作。Service 应进行：

- confidence threshold；
- temporal confirmation；
- cooldown；

最后输出“一个语义事件”，而不是把每帧结果轰炸给 AppController。

## 5. 单核策略

- 不跟随相机原始 FPS 全速推理；
- 起步建议 2～5 inference FPS；
- active voice/local LLM 时可降低普通视觉频率；
- 只处理最新帧，不积压旧帧。

## 6. 数据记录

普通每帧 PersonObservation 不进入 SQLite。只有有产品价值的事件才由 Care/Feature 层决定是否记录。

## 7. 不负责

- 切 UI；
- Emergency 页面；
- Robot UART；
- Family 网络协议。

## 8. 引入版本

V0.4 或视觉功能实际开发时。