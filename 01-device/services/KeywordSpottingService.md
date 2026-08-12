# KeywordSpottingService

[← Services](README.md)

## 1. 定位

宠物本体必须保留的本地语音入口。

负责：

- 本地关键词/唤醒词模型；
- 连续消费短 PCM frame；
- debounce/cooldown；
- 发出语义化关键词事件。

## 2. 推荐接口

```cpp
void start();
void stop();
void acceptAudio(const AudioFrame& frame);

signals:
    void keywordDetected(Keyword keyword);
    void error(QString message);
```

## 3. 为什么必须本地

即使 AI Server 断开，宠物仍需要能识别最基本的关键词并执行本地功能或给出明确反馈。

## 4. 与完整 ASR 的边界

KWS 不是长句 ASR。

```text
KWS：本地、常驻、低成本
ASR：优先远端服务器、按会话启动
```

## 5. Speaking 期间

第一版建议由 AudioService 暂停或抑制 KWS，防止宠物 TTS 自己触发自己。

## 6. 实现

底层模型细节进入 `SherpaKeywordEngine` 等 Platform Adapter，Service 不直接散落模型路径和 C API。

## 7. 引入版本

V0.3。