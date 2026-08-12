# 持久化规则

[← Data](README.md)

## 1. 什么应该持久化

- Reminder；
- Reminder 完成记录；
- 需要家属查看的 CareEvent；
- 用户设置；
- 配对信息；
- 必要版本元数据。

## 2. 什么不应该默认持久化

- 每帧人体识别；
- 每个 KWS 中间分数；
- PCM 音频；
- Camera frame；
- Remote AI token stream；
- UI 动画状态。

## 3. eMMC 写入

高频事件应先在内存聚合，只有产生业务意义时才落库。

## 4. 时间

数据库推荐存绝对 timestamp；UI 再按本地时区显示。每日 Reminder 规则则保留本地时间语义，并在系统时间/时区变化后重新调度。

## 5. Journal Mode

WAL 是否启用需要结合 Buildroot、并发和断电场景实测，不要仅因桌面经验默认开启。

## 6. 备份

数据库较小时，可以在版本升级或关键配置变更前做安全快照；不要频繁复制数据库造成额外写放大。