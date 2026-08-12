# 线程模型

[← Runtime](README.md)

## 1. 起步推荐

不要按桌面多核思维“一个功能开几个线程”。

可以从：

```text
Qt Main/UI Thread
Audio capture/KWS worker
Vision/heavy inference worker
Connectivity async event loop（必要时独立 QThread）
```

开始，具体数量由实测决定。

## 2. UI Thread 只做

- QWidget；
- paintEvent；
- 页面切换；
- signal/slot；
- 轻量 Timer；
- 小型 Model 更新。

## 3. UI Thread 禁止

```text
OrtSession::Run
本地 LLM generation
阻塞 snd_pcm_read
阻塞 socket recv
大图像 preprocess
sleep()
长数据库 migration
```

## 4. Audio

Audio capture 需要及时，不应被 Vision inference 阻塞。使用小型 bounded ring/buffer 将采集和 KWS/上传解耦。

## 5. Vision

Camera capture 可以是独立 worker；Perception 只取最新帧。视觉推理不需要积压队列。

## 6. SQLite

V0.2 小型、低频 SQL 若实测不阻塞，可同步调用。

如果后续写入/查询明显影响 UI，再增加**一个串行 DB worker**。Qt SQL connection 必须在所属线程创建和使用。

## 7. Connectivity

优先异步 socket。若高频音频发送影响 UI event loop，再将 Transport 移到自己的 QThread。

## 8. QObject 生命周期

跨线程对象明确 `moveToThread()`，退出时先 stop/cancel，再 quit/wait；不要让 worker 持有 QWidget。