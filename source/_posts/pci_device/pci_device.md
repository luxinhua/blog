---
title: PCI 设备访问
date: 2021/2/22
categories:
- PCI
---

---
### win 10 列出PCI设备
---
~~~c
wmic path win32_pnpentity where "deviceid like '%PCI%'" get name,deviceid
~~~
![](pci.png)

