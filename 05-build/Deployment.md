# 2K0300 部署

[← Build](README.md)

## 1. 交叉编译 SDK

沿用当前验证环境：

```text
/opt/loongarch64-buildroot-linux-gnu_sdk-buildroot
```

编译器：

```text
bin/loongarch64-loongson-linux-gnu-gcc
bin/loongarch64-loongson-linux-gnu-g++
```

sysroot：

```text
loongarch64-buildroot-linux-gnu/sysroot
```

## 2. 推荐目标目录

最终以 Buildroot 镜像策略为准，概念上：

```text
/opt/longpet/bin/LongPet
/opt/longpet/models/
/etc/longpet/longpet.ini
/var/lib/longpet/longpet.db
/var/lib/longpet/keys/
/var/log/longpet/
```

## 3. Qt

板端：

```text
linuxfb + tslib
```

Windows 只作为 UI/逻辑开发环境，不等价于板端性能验证。

## 4. 启动脚本

Buildroot 常见使用 init script，不要假定 systemd 一定存在。

启动顺序考虑：

- 文件系统可写；
- ALSA device ready；
- camera 可延后；
- 网络/蓝牙不阻塞 UI；
- DB migration 完成；
- Qt 环境变量准备。

## 5. Release

板端所有 CPU/RSS 验收都使用 Release。

## 6. 模型部署

模型与代码版本分别记录。Local LLM/vision/KWS 模型升级后应能从日志/Engineering 页面看出当前 model version，便于复现实验。