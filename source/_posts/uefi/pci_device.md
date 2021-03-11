---
title: UEFI --- pci 遍历
date: 2021/3/11
categories:
- uefi
---

### windows 上遍历PCI设备 | Reference [Blog](https://blog.csdn.net/u013983194/article/details/46960147)
~~~c
#include <stdio.h>
typedef unsigned long DWORD;
typedef unsigned int WORD;
#define MK_PDI(bus,dev,func) (WORD)((bus<<8)|(dev<<3)|(func))
#define MK_PCIaddr(bus,dev,func) (DWORD)(0xf8000000L|(DWORD)MK_PDI(bus,dev,func)<<8)
#define PCI_CONFIG_ADDRESS 0xCF8 
#define PCI_CONFIG_DATA 0xCFC
DWORD inpd(int inport)
{
    DWORD data;
    __asm(
        "mov dx,inport"
        "lea bx,data"
        "-emit 0x66,0x50"
        "-emit 0x66,0xED"
        "-emit 0x66,0x89,0x07"
        "-emit 0x66,0x58"
    );
    return data;
}

void outpd(int outport,DWORD addr)
{
    __asm(
        "mov dx,outport"
        "lea bx,addr"
        "-emit 0x66, 0x50"
        "-emit 0x66, 0x8B, 0x07"
        "-emit 0x66, 0xEF"
        "-emit 0x66, 0x58"
    );
}
DWORD GetData(DWORD addr)
{
    DWORD data;
    outpd(PCI_CONFIG_ADDRESS,addr);
    data = inpd(PCI_CONFIG_DATA);
    return data;
}

int main()
{
    int bus,dev,func;
    DWORD addr,addr1,addr2,addr3;
    DWORD data,data1,data2,data3;
    printf("Bus#\tDev#\tFunc#");
    printf("\n");
    for (bus = 0; bus <= 0x63; ++bus)
    {
        for (dev = 0; dev <= 0x1F; ++dev)
        {
            for (func = 0; func <= 0x7; ++func)
            {
                addr = MK_PCIaddr(bus,dev,func);
                data = GetData(addr);
                if((WORD)data!=0xFFFF) 
                {
                    printf("%2.2x\t%2.2x\t%2.2x\t",bus,dev,func);
                    printf("\n"); 
                }
            }
        }
    }
    return 0;
}
~~~