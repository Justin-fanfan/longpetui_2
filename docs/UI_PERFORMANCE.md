# LongPet Qt Widgets / linuxfb UI 性能整改

> 目标环境：Loongson 2K0300、单核 LA264 1.0 GHz、512 MB RAM、Qt 6 Widgets、linuxfb、1024×600、Release。  
> 本文记录代码层渲染整改。当前 Windows 环境不能替代板端测量，因此不声明具体板端 CPU 降幅。

## 1. 原因分析

整改前，`PetFaceWidget` 使用一个固定 83 ms（约 12 FPS）的持续 `QTimer`。只要允许动画且控件可见，每次 timeout 都会递增 `m_tick` 并执行无参数 `update()`。由此产生三类浪费：

- 所有表情都有约 1.2% 的持续 breathing 缩放，即使视觉几乎没有变化也每秒重绘约 12 次。
- Listening、Thinking、Speaking 的真实离散状态约每 3～4 个 tick 才变化一次，但中间帧仍会重画整个控件。
- 每次 paint 都重新启用整脸抗锯齿、变换坐标，并重新创建眼睛、嘴、曲线和装饰路径。

在无 GPU 假设的 linuxfb raster 路径上，大尺寸整脸的重复抗锯齿和合成会直接占用单核 CPU。

## 2. 新调度策略

持续 breathing 已完全删除，不再计算 `sin/cos` 或缩放整张脸。`setAnimationEnabled(true)` 现在表示“允许当前表情使用必要动画”，不再表示永远启动持续 timer。

| Expression | 新策略 | 主动刷新率 |
| --- | --- | --- |
| Default | 低频 one-shot blink | 平时 0 FPS；约 4.8～6.9 秒一次眨眼 |
| Default 2 | 低频 one-shot blink | 平时 0 FPS；约 4.8～6.9 秒一次眨眼 |
| Playful | 静态 | 0 FPS |
| Happy | 静态 | 0 FPS |
| Worried | 静态 | 0 FPS |
| Angry | 静态 | 0 FPS |
| Cute Cat | 静态 | 0 FPS |
| Sleep | 静态 | 0 FPS |
| Alert | 静态 | 0 FPS |
| Listening | 2 个离散波纹 phase | 240 ms，约 4.2 FPS |
| Thinking | 3 个离散点 phase | 320 ms，约 3.1 FPS |
| Speaking | `短→中→长→中` 4 phase | 220 ms，约 4.5 FPS |

每次持续动画 timeout 都会切换到真实的新视觉 phase，不再存在“状态没变却 repaint”的中间帧。

### Blink

Default、Default 2 使用成员 single-shot `QTimer`：

1. 正常状态不运行帧循环，只等待一次低频 timeout。
2. timeout 后切换闭眼，仅更新两眼 dirty region。
3. 150 ms 后恢复睁眼，仅更新两眼区域。
4. 再安排下一次 4.8～6.9 秒的 blink。

Listening 和 Speaking 也可独立使用同一低频 blink timer；眨眼不会改变其 4～5 FPS 动画时钟，也不会扩大为整脸帧循环。

## 3. 静态 QImage 缓存

每个 `PetFaceWidget` 只保留当前 expression、当前实际尺寸和当前 device pixel ratio 的静态 `QImage`：

- 缓存包含该控件完整背景和全部固定五官。
- 抗锯齿、逻辑坐标缩放与静态 `QPainterPath` 只在创建缓存时执行一次。
- 动画 paint 以 1:1 `drawImage` 恢复缓存像素，再画少量动态覆盖元素；Listening 的固定波纹路径也只在首次使用时创建一次。
- Default 系列在第一次实际 blink 时才按需额外生成闭眼缓存。
- expression、widget size、compact、背景色或 DPR 改变时缓存失效并重建。

没有全局缓存，也没有一次性缓存 12 个表情或大量动画帧，避免在 512 MB 设备上扩大内存占用。

`PetFaceWidget` 现在负责填充自己的固定背景，并启用 `WA_OpaquePaintEvent`，减少父级背景传播。Gallery 卡片显式把脸背景设为对应的 Surface/Selected Surface，保持原有卡片视觉。

## 4. 动态层与 dirty region

静态缓存不包含动态覆盖层。局部 repaint 时先由缓存恢复旧区域，再绘制当前 phase，因此不会累积透明像素或产生拖尾。

- Listening：只提交左右两个波纹区域的 `QRegion`，不提交脸中央。
- Thinking：只更新右上三个黄色点区域。
- Speaking：`ω` 嘴在静态缓存中，只更新右侧黄色说话线区域。
- Blink：只更新覆盖左右眼的区域。

逻辑矩形从 512×256 坐标映射到控件实际像素，并带 12 logical px 的抗锯齿安全边距。resize 后按最终实际尺寸重建缓存，动画帧不执行实时缓存缩放。

## 5. UI Gallery 与页面生命周期

Gallery 默认仅第一张选中表情允许其必要动画；其他 11 个 `PetFaceWidget` 均 `setAnimationEnabled(false)`。点击另一张卡片时，旧卡片 timer 立即停止，新卡片按自身 expression 决定是否需要 timer。静态表情即使被选中也保持 0 FPS。

ConversationPage 仍每页只有一张主脸。`hideEvent()` 会停止动画与 blink timer；`showEvent()` 仅根据当前 expression 恢复真正必要的 timer。Companion 当前展示的 Speaking 视觉被显式设为静态，避免待机页持续消耗 CPU。

## 6. 修改前后对比

| 项目 | Before | After |
| --- | --- | --- |
| 全局时钟 | 所有启用动画的可见脸固定 83 ms | 仅动态表情使用 expression 专属 interval |
| Default | 约 12 FPS 整脸 breathing + 帧计数等待 blink | 平时 0 FPS + one-shot blink |
| 静态表情 | 持续约 12 FPS | 0 FPS |
| Listening | 12 FPS 整控件 update；视觉 phase 低频变化 | 约 4.2 FPS，只更新左右波纹 |
| Thinking | 12 FPS 整控件 update | 约 3.1 FPS，只更新黄色点 |
| Speaking | 12 FPS 整控件 update；线条约 249 ms 才变化 | 约 4.5 FPS，每次都是新 phase，只更新黄色线 |
| 静态五官 | 每帧重建和抗锯齿 | 当前尺寸 QImage 一次渲染、后续 blit |
| breathing | 持续 `sin` + scale | 已删除 |
| Gallery | 选中项 12 FPS；静态脸也持续刷新 | 最多一个表情获准动画；静态选中项仍 0 FPS |

## 7. Windows 视觉与构建验证

- 使用独立 `Release` 目录和 Qt 6.11 MinGW 64-bit 完成构建。
- 自动抓取 15/15 个页面，逻辑画布均为 1024×600。
- 已检查 Companion、Control、Listening、Thinking、Speaking、Emergency、Sleep 和包含全部 12 表情的 Gallery。
- 缓存使用纯 Qt 6 Core/Gui/Widgets raster API，不依赖 Windows API、OpenGL、QML、线程或 GPU 特效。

Windows 截图只能验证静态视觉和尺寸，不能代表 linuxfb 的 CPU 数字。动态残影仍应在实际 linuxfb framebuffer 上观察确认。

## 8. 2K0300 板端 A/B 测试

必须使用相同硬件、系统镜像、Qt 配置、屏幕、Release 编译选项和测试时长比较优化前后版本。建议每次开机后先空闲 30 秒，并分别测试旧版本和新版本至少两轮。

BusyBox 兼容的基本步骤：

```sh
pidof LongPetUiDemo
top
```

如果 `top` 支持按 PID 过滤，可使用：

```sh
top -p "$(pidof LongPetUiDemo)"
```

依次保持以下页面 30 秒，记录稳定后的 CPU% 与 RES/内存：

1. Companion / Default
2. Control / Default 2
3. Listening
4. Thinking
5. Speaking
6. Sleep
7. UI Gallery（不点击，随后选中 Speaking 再测一次）

同时人工检查：

- blink 是否完整且没有眼部裁切；
- Listening 左右波纹切换是否无残影；
- Thinking 黄色点是否无拖尾；
- Speaking 黄色线是否无叠亮或残影；
- Gallery 切换选择后，旧卡片动画是否立即停止；
- 页面切走后对应进程 CPU 是否回落。

内部目标为：静态页面低于 5%，Listening/Thinking/Speaking 明显低于整改前约 60%，Speaking 目标低于 15%、最低持续低于 20%。这些数字必须由 2K0300 实机验证，当前代码层验证不能替代该结论。
