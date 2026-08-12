# ConnectivityManager

[← Services](README.md)

## 定位

维护“有哪些链路和端点现在可用”的状态。

## 可以维护

```text
Network available
Bluetooth available
AI Server endpoints
Family link endpoints
selected AI transport
last successful endpoint
```

## 不负责

- ASR；
- Family command 业务；
- UI 页面；
- Socket message decode。

## 为什么不是 PetStateMachine 状态

连接是正交上下文。宠物可以处于 Companion，同时网络断开/连接；不应该为此制造 `CompanionOnline/CompanionOffline` 等状态。

## 选择策略

Remote AI 新 session 建立前，可根据：

```text
可用性
延迟
稳定性
用户设置
服务器 capability
```

选择 Network 或 Bluetooth。

## 是否必须独立类

第一版如果只有一个固定服务器地址，可以让 RemoteAiService 内部管理。等链路发现、fallback 和多端点真正出现后再提取。