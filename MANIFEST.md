# 文档包清单

[← 根目录](README.md)

本交付分支只包含 LongPet 架构 Markdown 文档，不包含 UI 源码。

## 顶层入口

- [README.md · 总体架构与可点击树](README.md)
- [ARCHITECTURE_RULES.md · 架构决策与约束](ARCHITECTURE_RULES.md)
- [CLASS_INDEX.md · 类/文件快速索引](CLASS_INDEX.md)
- `MANIFEST.md` · 当前文档

## 模块目录

- [01-device/ · 宠物本体](01-device/README.md)
- [02-external/ · 外部系统边界](02-external/README.md)
- [03-flows/ · 关键数据流](03-flows/README.md)
- [04-runtime/ · 运行时、性能与可靠性](04-runtime/README.md)
- [05-build/ · 构建、配置与部署](05-build/README.md)
- [06-roadmap/ · 版本演进](06-roadmap/README.md)

`01-device/` 继续细分为：

- [app/](01-device/app/README.md)
- [ui/](01-device/ui/README.md)
- [model/](01-device/model/README.md)
- [services/](01-device/services/README.md)
- [data/](01-device/data/README.md)
- [platform/](01-device/platform/README.md)
- [connectivity/](01-device/connectivity/README.md)
- [features/](01-device/features/README.md)

## Markdown 导航约束

真正需要点击的相对链接必须写在普通 Markdown 内容中，例如：

```markdown
- [AppController](01-device/app/AppController.md)
```

不要把“要点击的链接”放在 fenced code block 中。代码块中的 `[text](path)` 只会显示成纯文本，不会被 GitHub 或 VS Code Markdown Preview 渲染成超链接。

根 README 的长期目录已经改为嵌套 Markdown 列表，因此目录层级仍然清楚，同时每一项都可点击。