# BluetoothTransport

[← Connectivity](README.md)

## 定位

为宠物与 AI Server 的近距离连接提供第二 Transport。

## 不预设具体承载

最终可能是：

- Bluetooth Classic 的串行/可靠通道；
- BLE GATT 分片；
- 其他板端已经稳定支持的方式。

应以 2K0300/Buildroot 的蓝牙栈实测决定。

## 与网络的差异

协议层不能假设 Bluetooth 与 LAN 有相同：

```text
MTU
吞吐
延迟
稳定性
```

必须有：

- 分片/重组；
- seq；
- 最大队列；
- timeout；
- capability/audio format negotiation。

如果原始 PCM 带宽不合适，协议应允许协商压缩格式；具体 codec 再依据 CPU 与链路实测。

## 上层

对 AiServerClient 仍表现为 ITransport。