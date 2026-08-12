# SettingsService

[← Services](README.md)

## 职责

- 读取/保存用户设置；
- 校验设置范围；
- 将设置应用到对应系统模块；
- 发出 settingsChanged。

## 典型设置

```text
volume
brightness
pet preferences
AI usage preference
family configuration
```

## 数据边界

普通用户设置可以通过 SettingsRepository 保存。

真正的 ALSA mixer、背光 `/sys`、Bluetooth 配对操作下沉到 Platform/Connectivity。

## 与 RuntimeConfig 区别

SettingsService：用户可改的产品设置。

RuntimeConfig：部署/开发配置，如模型路径、server discovery 模式、日志级别等。两者不要混在同一张 settings 表。