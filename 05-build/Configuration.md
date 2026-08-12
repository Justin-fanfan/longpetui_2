# 运行时配置

[← Build](README.md)

## 1. RuntimeConfig 与用户 Settings 分开

### RuntimeConfig

部署/开发参数，例如：

```text
model paths
AI Server discovery mode
preferred transport
log level
feature flags
database path
connection timeout
```

### SettingsService

老人/家属真正可以改变的产品设置：

```text
volume
brightness
pet preference
reminder settings
```

不要全部塞到 SQLite `settings` 表。

## 2. 推荐文件

例如：

```text
/etc/longpet/longpet.ini
```

或 JSON/TOML。格式不是重点，关键是统一读取。

## 3. 环境变量

适合平台启动项：

```text
QT_QPA_PLATFORM=linuxfb
TSLIB_*
```

开发路径可通过环境变量覆盖，但生产默认值明确。

## 4. 模型路径

统一由 RuntimeConfig 提供：

```text
/opt/longpet/models/...
```

不要在多个 Service 中重复硬编码。

## 5. Secret

配对 token、证书/密钥不要进入普通明文部署配置仓库。保存到权限受限的独立数据目录。