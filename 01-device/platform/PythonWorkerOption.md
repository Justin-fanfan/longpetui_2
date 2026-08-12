# Python AI Worker：可选实现方案

[← Platform](README.md)

## 背景

现有环境已经具备 Python/OpenCV/ONNX Runtime/sherpa-onnx 能力。某些已有算法如果主要是 Python，正式 LongPet 不必为了“架构纯 C++”立即全部重写。

## 方案 A：C++ 直接 Adapter

优点：

- 进程更少；
- 内存更可控；
- 无 IPC；
- Qt/C++ 生命周期统一。

适合已经稳定且 C++ API 清晰的模块。

## 方案 B：一个长期驻留 Python Worker

```text
LongPet Qt process
    ↕ Unix domain socket / framed pipe
longpet-ai-worker Python process
```

适合大量现有 Python 推理代码复用。

## 禁止的方式

```text
每识别一次
→ QProcess 启动 python
→ load model
→ inference
→ exit
```

这会严重浪费 CPU、内存和延迟。

## 单核/512MB 注意

Python Worker 会带来额外解释器和库 RSS。必须实测总内存，不能同时常驻多份模型副本。

## IPC

传语义结果优先；摄像头大帧若跨进程，需要共享内存/受控 buffer，避免反复大拷贝。

## 决策原则

先复用能跑通的实现，再根据 RSS/延迟热点决定是否将某模块迁移到 C++。架构边界保持不变，上层 Service 不需要因实现语言变化而改。