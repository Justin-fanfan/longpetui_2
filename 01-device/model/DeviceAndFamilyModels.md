# Device / Family DTO

[← Model](README.md)

## DeviceSummary

给家属端/设置页使用的经过筛选摘要：

```text
deviceId
online/uptime
softwareVersion
battery/power
storageSummary
aiServerReady
lastUpdated
```

不要把整个 AppState 或 `/proc` 原始文本发给 Electron。

## FamilyCommand

解析后的白名单命令：

```text
commandType
requestId
payload
senderIdentity
```

进入业务 Service 前还需权限和字段校验。

## CommandResult

```text
requestId
success
errorCode
message
newRevision（如适用）
```

## PairingRecord

只保存必要的配对身份/凭证元数据。敏感 secret 的存储方式由 Security 文档约束。