# ConversationPage

[← Pages](README.md)

## 定位

共用一套沉浸布局显示：

```text
Listening
Thinking
Speaking
```

## 推荐类型

```cpp
enum class ConversationMode {
    Listening,
    Thinking,
    Speaking
};
```

## 推荐接口

```cpp
void setMode(ConversationMode mode);
void setTranscript(const QString& text);
void setReplyText(const QString& text);

signals:
    void cancelRequested();
```

## 与语音模块的边界

页面只接收：

```text
partial/final transcript
reply text
current conversation state
```

页面不知道：

- 音频来自 ALSA；
- ASR 在 AI Server；
- 当前走 Wi-Fi 还是 Bluetooth；
- TTS 音频格式。

## 性能

继续复用当前低 FPS `PetFaceWidget`：Listening/Thinking/Speaking 不需要 60 FPS。

## 引入版本

Remote AI 语音链路开发时，建议 V0.3。