---
title: PCI 设备
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


---
### base 
---
    Pcie 
        256 bus 
            每条bus 挂 32 devcie 
                每个设备有 8 func 
                    每个设备空间有 PCI 256Byte PCIE 4K 
    所以PCIE　总共大小是，　４K * 256 * 32 * 8 = 256 K Byte = 256 M 

    PCIE 配置空间也可以 mem map / IO map. 
        IO map/访问： 
            只能PCIE 前256Byte， 后面的要用MMap 访问
            example (IO access): 
                1 /*Access PCI Config Space in IO method*/
                2 Address = BIT31|((BUS & 0XFF)<< 16)|((DEV & 0x1F)<<11)|((Fun & 0x7) << 8);
                3 IoWrite32(0xCF8, address);                 //将要读取的地址写入到CF8
                4 Date32 = IoRead32(0xcfc);                  //从CFC端口读出address的数据
        mem map/访问: 
            example:
            1 /*Write date*/
            2 MmioWrite32(PcieBaseAdd + Bus<<16 + Dev<<11 + Fun<<8 + offset, date); //PcieBaseAdd为PCIE在内存中的基地址
            4 /*Read date*/ 
            5 Value = MmioRead32(PcieBaseAdd + Bus<<16 + Dev<<11 + Fun<<8 + offset);

---
### 配置空间（ 普通设备 ）位说明： 
---	
---
### PCIe 桥 （ 透明桥 ）
---

	连接在PCIe 接口上的一个设备，只是配置空间和普通PCIE 设备不同，桥设备只有在遍历设备时才配置，不需要专门的驱动，所以叫透明桥
	PCI桥的配置空间在前16个字节的格式和普通PCI设备并无区别，另外，桥还保留了普通设备的前两个BAR空间。所以从配置空间的0x18开始有了桥设备自身的配置格式

---
### 各种地址类型： 
---
	1. Pcie 空间： 
	   GnbLibPciRead 

---
### PCI/PCIe 空间分布，访问方式
---
    PCI 
    0-255 PCI config space 
    0-63  PCI config space header 
        2种类型的头有部分寄存器相同，叫 common header 
        type 0  
            其他设备，
        type 1 
            专门给桥用
    64-255 PCI capability list. 功能的链表， 入口在 header中的0x34偏移的一个寄存器中
        每一个capability item 大小长度不一样，所以可以实现不同的功能。
        但是所有的capability item , 在cap header 里有标准的描述头，方便设备扫描，穷举。
        capability item 的类型也有范围限制。
    256-4095  extend config space    PCIE 引入
        里面存整条 extend capability list, 第一个节点从256 （0x100）开始，
        extend cambility list也有一个标准化的 extend cap header
        extend cap header 与 cap header  ， 其中ID可以重名， 因为物理地址隔离，所以不怕重名。 
    PCI 访问方式： 	
        IO 指令：  index/data 方式 , IO 方式只能访问 0-255 这个方位的，后面的拓展只能通过MMIO 访问
            0xCF8 写入地址，
            0xCFC 读写数据
        MMIO， 这就看系统怎么映射了，找到基地址，找到offset, 进行访问
