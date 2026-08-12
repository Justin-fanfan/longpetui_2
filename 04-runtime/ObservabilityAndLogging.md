# 日志与可观测性

[← Runtime](README.md)

分布式链路加入后，没有可关联日志会很难排查“宠物、AI Server、Electron 到底哪一段出错”。

## 1. 推荐日志字段

```text
timestamp
module
level
deviceId
requestId/sessionId（适用时）
errorCode
message
```

## 2. 关键指标

建议低频记录/工程页显示：

- UI CPU/RSS；
- vision inference latency；
- KWS latency/error；
- AI Server RTT/reconnect；
- speech session total latency；
- TTS buffer underrun；
- SQLite error/migration version；
- Robot driver error。

## 3. 不要每帧打印

```cpp
qDebug() << "frame";
```

在动画、AudioFrame、CameraFrame 等热路径中持续打印会显著干扰性能。

## 4. 文件日志

推荐有大小上限和轮转，防止 `/var/log` 长期写满 eMMC。

## 5. Correlation

Remote speech 的 `sessionId` 应同时出现在：

```text
pet RemoteAiService log
AiServerClient log
AI Server log
```

这样比赛现场或长期测试时可以快速定位一整次会话。

## 6. 隐私

日志记录“ASR success/failure、长度、耗时”通常比记录完整老人语音文本更安全。确需文本调试时使用显式开发开关。