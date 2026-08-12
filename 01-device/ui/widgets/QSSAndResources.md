# QSS 与 Resources

[← Widgets](README.md)

## app.qss

继续统一负责：

- 字体；
- QPushButton；
- pressed/disabled；
- Card；
- Slider；
- Toast；
- Warning/Danger/Success；
- UI Gallery 开发样式。

不要把正式页面重新变成大量 `widget->setStyleSheet()`。

## QRC

资源统一通过：

```text
:/styles/app.qss
:/icons/...
```

访问。

禁止运行时依赖：

```text
C:\Users\...
/home/...
/root/...
```

## SVG

保持简化、无 blur/filter/复杂 mask。对 2K0300 以几何简单、一次缓存为主。