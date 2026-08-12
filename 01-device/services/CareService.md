# CareService

[← Services](README.md)

## 定位

将 Reminder、活动和本地互动事件整理为统一 `CareSummary`。

## 数据来源

```text
Reminder completion events
CareEventRepository
Creative feature interactions
可选传感器数据
```

## 输出

```text
water progress
medicine summary
activity summary
interaction summary
lastUpdated
```

## 消费者

- CarePage；
- FamilyLinkService；
- 本地创意功能。

## 关键原则

CarePage 和 Electron 不应各自重新统计 SQLite，否则容易出现两个不同口径。

## 写入频率

不要把人体检测每帧写入 CareEvent。只记录真正有业务含义的事件。

## 引入版本

V0.2。