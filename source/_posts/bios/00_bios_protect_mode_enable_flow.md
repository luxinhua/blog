---
title: BIOS protect mode 总结
data: 2021/4/15
categories:
- bios
toc: true # 是否启用内容索引
# sidebar: none # 是否启用sidebar侧边栏，none：不启用

---
### 保护模式流程： 
---
	1. 准备GDT。
	2. 用lgdt加载gdtr。
	3. 打开A20。
	4. 置cr0的PE位。
	5. 跳转，进入保护模式。

---
### 汇编流程
---
~~~bash
; Save BIST state in EAX
mov     ebp,  eax   
; BspApCheck
mov     ecx, APIC_BASE_ADDRESS  ; MSR:0000_001B
rdmsr     // 读取ecx地址中的值，赋给 edx, eax( low 16 bit ) 
/*  
BSC: boot strap core. Read-write,Volatile. Reset: X. 
		0=The core is not the boot core of the BSP. 
		1=The core is the boot core of the BSP.
*/ 
// 找到最先启动的核
bt      eax, APIC_BSC           ; Is this the BSC?   APIC_BSC = 8, bt,检测某一位是否被置位， 这里就是检测第8位 




mov     esi,  OFFSET GdtDesc  // 初始化GDT把GDT地址赋给esi. 
	
	GdtDesc:                                                ; GDT descriptor
	OffsetGDTDesc       EQU     $ - Flat32Start
						DW      GDT_SIZE - 1                ; GDT limit
						DD      OFFSET BootGDTtable ; GDT base address
				
		汇编定义了 BootGDTtable， 里面有数据段，代码段等各段定义
				
DB      66h     // 本意是存储一个值为66H, 但是这里是80386芯片BUG 引入的命令用于切换16/32 位，
	
	66 8b c3  32位机器码命令
	8b c3     16位的命令

/*
	1. fword表示操作的是32位的地址 ， （ 配置上面的66 命令，确保是32位操作 ？）
	2. 之前包GDT的地址赋给了esi , si是esi的低16位，
	3， 这条命令是把，esi 低16位赋给GDTR寄存器，方便其他地方调用
*/
lgdt    fword ptr cs:[si]   
/*
	读出CR0(32位的控制寄存器)到eax ； 
		[0] PE  protect enable 是否启动保护模式
		[1] MP  moniter coprocessor 监控协处理器
		[2] EM  emulate coprocessor 模拟协处理器 = 1 无法使用协处理器
		[3] TS  task switch, 任务完成置1 ， 置1后无法使用协处理器
		[4] 微处理器的拓展位，处理器类型  287协处理器，387浮点协处理器
		[31] 分页使能，是否使用page机制
*/
mov     eax, cr0                           ; Get control register 0
/*
	启动保护模式 
	启动协处理器
*/
or      eax, 00000003h                     ; Set PE bit (bit #0) & MP bit (bit #1)
mov     cr0, eax                           ; Activate protected mode
/*
	读出CR４　
	[0] VME  virtaul-8086 mode extensions  给运行 invirtual-8086的软件硬件加速
	[1] PVI  protect-mode virtaul interrupt support. ( 中断反应在 RFLAGS 寄存器红的 VIF/VIP 2个bit中 )
	[2] TSD  time-stamp disable  0/1 表示是否可以读取 RDTSC/RDTSCP 
	[3] DE   Debug extension , enable IO breakpoint. 
	[4] PSE  page-size extension
	[5] PAE  物理地址拓展， 使能的话，支持2M的超级页 
	[6] MCE  machine-check enable 
	[7] PGE  page global enable
	[8] PCE  performance-monitoring counter enable 
	[9] OSFXSR  256/128bit media 指令使能
	[10] OSXMMEXCPT enable 处理 256/128bit media 指令异常 
*/
mov     eax, cr4                           ; Get control register 4
or      eax, 00000600h                     ; Set OSFXSR bit (bit #9) & OSXMMEXCPT bit (bit #10)
/*
	使能这俩位
	[9] OSFXSR  256/128bit media 指令使能
	[10] OSXMMEXCPT enable 处理 256/128bit media 指令异常 			
*/
mov     cr4, eax



// 段初始化
mov     ax, SYS_DATA_SEL   // 复制申请的系统数据段的地址给ax 
	
	; System data segment descriptor
	SYS_DATA_SEL        equ     $ - GDT_BASE               ; Selector [0x18]
						DW      0FFFFh                     ; limit 0xFFFFF
						DW      0                          ; base 0
						DB      0
						DB      093h                       ; present, ring 0, data, expand-up, not-writable
						DB      0CFh                       ; page-granular, 32-bit
						DB      0
						
// 同样的地址赋给各个段寄存器
mov     ds, ax
mov     es, ax
mov     fs, ax
mov     gs, ax
mov     ss, ax 
// 目前前面都是在protect 16模式下 


; Go to Protected32  
mov esi, offset NemInitLinearAddress
	
	NemInitLinearAddress   LABEL   FWORD // 没有定义东西

jmp     fword ptr cs:[si]   // 这里是个逻辑地址， 
~~~

