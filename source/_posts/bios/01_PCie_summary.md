---
title: BIOS protect mode 总结
data: 2021/4/15
categories:
- Pcie
toc: true # 是否启用内容索引
# sidebar: none # 是否启用sidebar侧边栏，none：不启用

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