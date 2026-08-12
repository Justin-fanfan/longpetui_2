# EmergencyPage

[← Pages](README.md)

## 定位

最高优先级的安全交互 UI。

## 推荐 signal

```cpp
signals:
    void userConfirmedSafe();
    void contactFamilyRequested();
```

## 特点

- 不需要用户先进入 Control；
- 可以覆盖 Companion/Conversation；
- 按钮必须大、文案明确；
- 应能立即取消普通 TTS/机器人动作。

## 不负责

- 视觉异常检测；
- 网络联系家属；
- 发送消息；
- 安全判定模型。

这些由 Service + AppController 完成。

## 引入版本

有明确异常检测/联系家属闭环时再加入正式业务。