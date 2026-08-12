# SettingsPage

[← Pages](README.md)

## 定位

显示和编辑用户可见设置。

## 可能内容

- 音量；
- 屏幕亮度；
- 宠物偏好；
- AI Server 使用偏好；
- 家属配对状态；
- 关于设备。

## 输出

页面只发出语义化修改请求，例如：

```text
volumeChangeRequested
brightnessChangeRequested
pairFamilyRequested
```

## 不负责

- ALSA mixer；
- `/sys/class/backlight`；
- Bluetooth pairing 底层；
- SQLite。

由 SettingsService/Connectivity 完成。

## 引入版本

V0.2 起逐步加入。