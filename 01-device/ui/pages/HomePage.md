# HomePage / Control Page

[← Pages](README.md)

## 定位

用户主动触摸 Companion 后出现的 Control UI。

## 显示

- StatusBar；
- 宠物脸；
- 陪伴文案；
- 陪我说话；
- 今日关怀；
- 提醒；
- 设置入口。

## 正式 signal

```cpp
signals:
    void talkRequested();
    void careRequested();
    void reminderRequested();
    void settingsRequested();
```

不要继续把 `QPushButton*` getter 当成正式业务 API。

## Timeout

HomePage 本身不决定 12～15 秒后去哪里。V0.1 可暂由 MainWindow 管；引入 AppController 后由 Application 层控制。

## 数据

时间、天气、摘要等以后通过 setter/Model 输入，不在页面内部联网或查询 SQLite。

## V0.1

首批迁入正式工程。