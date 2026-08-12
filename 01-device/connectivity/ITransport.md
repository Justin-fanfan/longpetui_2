# ITransport

[← Connectivity](README.md)

## 定位

统一“可靠发送/接收一段 framed message”的底层传输能力，让 RemoteAiService 不关心当前是网络还是蓝牙。

## API 方向

实际 Qt 版本可使用 QObject + signal：

```cpp
class ITransport : public QObject
{
    Q_OBJECT
public:
    virtual void connectToEndpoint(const Endpoint&) = 0;
    virtual void disconnectFromEndpoint() = 0;
    virtual void sendFrame(const QByteArray&) = 0;

signals:
    void connected();
    void disconnected(...);
    void frameReceived(QByteArray);
    void errorOccurred(...);
};
```

## 语义

ITransport 只解决：

```text
connect
send frame
receive frame
disconnect
```

不认识：

```text
ASR
TTS
Reminder
FamilyCommand
```

## 为什么值得抽象

这里存在真实的多实现：

```text
NetworkTransport
BluetoothTransport
```

不是为了形式而创建接口。