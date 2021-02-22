---
title: UEFI --- env 语法
date: 2021/2/22
categories:
- uefi
---

---
### 内容
---

好像都是定义的宏，要用项目的feature控制
类似如下： 
~~~bash
EDK_GLOBAL  EMULATIO_XX_ONLY                          = NO
EDK_GLOBAL  EMULATIO_XX_GIO_ONLY                      = YES
~~~