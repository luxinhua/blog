---
title: risc-v cpu simulator ( 流水线 )
date: 2021/9/28
categories: cpu-simulator
---

---
### 背景１：RISC-V 工具链以及指定指令集编译生成测试ELF文件
---
[Reference](https://blog.csdn.net/DP29syM41zyGndVF/article/details/106110178)

---
### 背景２：ELF深入浅出
---
[EFL Doc](https://paper.seebug.org/1289/)

---
### 背景3：虚拟内存
---
[虚拟内存](https://xie.infoq.cn/article/7ea65943509986f5c1f77bc30)


---
### 背景4：ｃ语言各个段的分布以及验证
---
[reference](https://www.cnblogs.com/zafu/p/7399859.html)
1. 用objdump -d -s  看下有哪些段。
~~~bash
    $ objdump.exe -s a.out.exe | grep 'Contents of section'
    Contents of section .text:
    Contents of section .data:
    Contents of section .rdata:
    Contents of section .buildid:
    Contents of section .pdata:
    Contents of section .xdata:
    Contents of section .idata:
    Contents of section .rsrc:
    Contents of section .reloc:
    Contents of section .debug_aranges:
    Contents of section .debug_info:
    Contents of section .debug_abbrev:
    Contents of section .debug_line:
    Contents of section .debug_frame:
    Contents of section .debug_str:
    Contents of section .debug_loc:
    Contents of section .debug_line_str:
~~~
2. 在代码里通过 __attribute((section(name))) 指定变量存放到对应段中，然后查看变量地址，查看各段的内存分布
3. main 
~~~c

~~~

---
### 
---


---
### 
---


---
### 
---

---
### 
---