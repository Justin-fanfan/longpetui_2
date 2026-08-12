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
motion protocol parameters
auto-follow safety limits
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

## 2. 运动配置属于哪一层

以下参数更接近硬件/安全部署配置，不建议默认暴露给家属端：

```text
max linear speed
max angular speed
motion command timeout
MCU heartbeat interval
MCU lease timeout
auto-follow enable default
auto-follow max speed
target stale timeout
```

它们应来自 `RuntimeConfig` 或 MCU 固件安全配置，并由 MotionService/Driver 读取。

用户设置最多只应暴露经过产品定义的高层选项，例如：

```text
是否启用自动跟随（如果产品允许）
跟随偏好：关闭 / 保守
```

即使用户选择“开启”，最终速度上限仍由系统安全配置约束，不能让 UI/Family App 任意扩大。

## 3. 推荐文件

例如：

```text
/etc/longpet/longpet.ini
```

或 JSON/TOML。格式不是重点，关键是统一读取。

## 4. 环境变量

适合平台启动项：

```text
QT_QPA_PLATFORM=linuxfb
TSLIB_*
```

开发路径可通过环境变量覆盖，但生产默认值明确。

## 5. 模型路径

统一由 RuntimeConfig 提供：

```text
/opt/longpet/models/...
```

不要在多个 Service 中重复硬编码。

## 6. MCU / Protocol

协议版本、设备路径、波特率等可属于 RuntimeConfig，例如：

```text
motion.device=/dev/ttySx
motion.baud=...
motion.protocolVersion=...
```

具体值由真实硬件确定，文档不预设。

安全上限若 MCU 固件也有一份，建议 MCU 的限制不宽于龙芯应用允许范围，形成双层限制。

## 7. Secret

配对 token、证书/密钥不要进入普通明文部署配置仓库。保存到权限受限的独立数据目录。