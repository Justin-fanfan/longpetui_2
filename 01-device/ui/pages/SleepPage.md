# SleepPage

[← Pages](README.md)

## 定位

夜间/休息时的低刺激视觉状态。

## 显示

- Sleep 表情；
- 可选大时间；
- 极少文字；
- 深色低刺激背景。

## 输入

```cpp
signals:
    void wakeRequested();
```

## 不负责

- Linux suspend；
- 背光驱动；
- KWS 是否继续运行；
- Wake policy。

这些由 AppController/Settings/System 决定。

## 引入版本

V0.2/V0.3，视产品睡眠策略而定。