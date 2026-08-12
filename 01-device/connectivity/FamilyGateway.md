# FamilyGateway

[← Connectivity](README.md)

## 定位

承载 Electron 家属端与宠物之间的**传输/协议会话**。

它和 `FamilyLinkService` 的区别：

```text
FamilyGateway：通信、配对、message framing、request/response
FamilyLinkService：业务权限、DTO、调用 Reminder/Care/Settings
```

## 网络拓扑不要过早写死

未来可能是：

### LAN Direct

```text
Electron → Pet local endpoint
```

### Outbound/Relay

```text
Pet → relay/server ← Electron
```

因此上层 FamilyLinkService 不应假定自己一定是 TCP Server 还是 Client。

## 职责

- pairing session；
- authenticated connection；
- request id；
- command/message decode；
- heartbeat；
- reconnect；
- push channel。

## 不负责

- 直接 SQL；
- 修改 Reminder；
- 决定家属是否能做某业务操作。