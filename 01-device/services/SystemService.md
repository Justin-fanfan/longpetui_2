# SystemService

[← Services](README.md)

## 定位

提供宠物本体少量系统状态摘要。

## 可能内容

- 电量/供电；
- 存储剩余；
- 网络摘要；
- 软件版本；
- 必要时温度；
- uptime。

## 消费者

- Settings/About；
- Engineering 页面；
- FamilyLinkService 的 DeviceSummary。

## 性能

正式产品不需要 100ms 高频读取 `/proc`。秒级甚至更低频足够。

## 不负责

不应变成“万能 Linux 工具类”。每个系统调用仍应有明确边界。