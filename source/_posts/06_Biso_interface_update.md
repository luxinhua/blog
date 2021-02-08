---
title: BiosInterFace update 的思路
data: 2021/2/8
categories:
- hexo
toc: true # 是否启用内容索引
# sidebar: none # 是否启用sidebar侧边栏，none：不启用
---

---
### 概念
---
* PMFW
  专门控制CLK/power的一个bin ,
* SMU
  BIOS的菜单控制，设置值，分发值到具体的模块
  SMU和PMFW通过msg机制更新biosinterfaceTable的结构体来通信。
* MSG机制
  一端，向某个寄存器写入消息ID，消息参数，poll 等待response，另一端是硬件中断，拿到硬件中断后，处理写入response消息。