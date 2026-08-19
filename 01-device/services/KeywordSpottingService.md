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

`Keyword` 应是语义枚举而不是页面直接比较原始字符串。例如可以包含：

```text
Wake
Emergency
ReminderAcknowledge
ReminderComplete
ReminderLater（可选）
```

## 3. 为什么必须本地

即使 AI Server 断开，宠物仍需要能识别最基本的关键词并执行本地功能或给出明确反馈。

提醒确认尤其适合 KWS：它只需要识别少量固定语义，不应依赖完整 ASR 或远端 AI。

## 4. 与 Reminder 的上下文边界

`ReminderAcknowledge` / `ReminderComplete` 只是语义事件，是否真正作用于 Reminder 必须由 AppController 根据当前 Attention/UI 上下文决定。

推荐：

```text
ReminderAlertPage active
+ keywordDetected(ReminderAcknowledge)
→ ReminderService::acknowledge(currentOccurrence, Voice)
```

而不是：

```text
任意页面听到“知道了”
→ 直接完成最近一条 Reminder
```

这样可以避免普通聊天、电视声音或老人日常说话误确认提醒。

## 5. 与完整 ASR 的边界

KWS 不是长句 ASR。

```text
KWS：本地、常驻、低成本
ASR：优先远端服务器、按会话启动
```

提醒确认第一阶段只需要 KWS，不必等待完整语音会话能力。

## 6. Speaking / Reminder playback 期间

普通 TTS Speaking 期间，第一版建议由 AudioService 暂停或抑制 KWS，防止宠物 TTS 自己触发自己。

Reminder 播报也必须考虑同样问题：应在播报结束后进入短暂确认监听窗口，或使用可靠的 echo/cooldown 策略，不能让提醒语音中的“知道了”等内容自触发确认。

## 7. 实现

底层模型细节进入 `SherpaKeywordEngine` 等 Platform Adapter，Service 不直接散落模型路径和 C API。

## 8. 引入版本

V0.3。提醒页面可在 V0.2 先提供触摸确认，KWS 接入后无缝增加语音确认。