# NetworkTransport

[← Connectivity](README.md)

## 定位

实现局域网/有线网络上的可靠双向传输。

## 技术选择

具体可选：

- TCP + 自定义 framing；
- WebSocket；
- 其他已验证协议。

应先确认 Buildroot 中实际可用的 QtNetwork/QtWebSockets 组件，再决定，不要让架构文档强迫增加大依赖。

## 必须支持

- non-blocking connect；
- reconnect；
- timeout；
- bounded send queue；
- message framing；
- 最大消息尺寸限制；
- keepalive/heartbeat 所需能力。

## 线程

优先使用 Qt 异步 socket/event loop，不要在 UI 线程做阻塞 recv/send。

## 上层

AiServerClient / FamilyGateway 使用它，但不把 socket 暴露给 Service。