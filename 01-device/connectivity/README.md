# Connectivity

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

Connectivity 层负责与外部节点建立可靠消息通道。

- [ITransport](ITransport.md)
- [NetworkTransport](NetworkTransport.md)
- [BluetoothTransport](BluetoothTransport.md)
- [AiServerClient](AiServerClient.md)
- [FamilyGateway](FamilyGateway.md)
- [Protocol](Protocol.md)

这里是少数**值得定义接口**的地方，因为 Remote AI 明确至少存在 Network 与 Bluetooth 两种 transport 实现。