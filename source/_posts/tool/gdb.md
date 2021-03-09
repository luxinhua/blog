---
title: gdb 调试常用命令备忘
categories:
- tools
date: 2021/3/9
toc: true # 是否启用内容索引
---


disassemble    //gdb下使用可以查看汇编代码
disassemble /m 函数名      /m 源码和汇编一起排列
disassemble 不带参数，默认的反汇编范围是 所选择帧的pc附近的函数
单个参数, 就是pc, 当然也可以是函数名，因为函数名 也是一个 地址; 
这样范围就是该pc附近的函数
两个参数，就是内存地址范围


使用display /i $pc（结合display命令和寄存器/pc内部变量）指令进行设置

info register查看寄存器的情况，可以简写成i r
主要是%eip、%eax、%esp和%ebp
 列出的结果主要有三行
    最左边是寄存器名称外，中间是寄存器存的值（也就是一个内存地址），右边是这个值对应的内存
    地址中的值。打印一下$eax可验证

si，ni：
    下一条语句遇到函数调用的时候，nexti不会跟踪进入函数，而是继续执行下面的语句，
    而step命令则会跟踪进入函数内部。
    si命令类似于s命令，ni命令类似于n命令。所不同的是，这两个命令（si/ni）所针对的是汇编指
    令，而s/n针对的是源代码。     
i代表指令（instruction）
     n(ext)i
     s(tep)i

$pc   代表pc程序计数器的值

set disassembly-flavor intel          gdb设置intel汇编 ，默认是att

print其实是有计数器的，每次print打印，其实都有一个类似count++在内部发生，
使用print $num 能显示第num个打印结果，如上，p $3   //查看第三个值
  (gdb)p i
  (gdb)p/a i
  (gdb)p/c i
  (gdb)p/f i
  (gdb)p/x i
  (gdb)p/o i
  (gdb)p/d i
  (gdb)p/t i               
	f浮点，c字符，t为二进制，o八，x十六，d十
	a和x同样是打印十六进制,不同名但同功能
	
调试运行中的程序：
   #ps -aux | grep execFile    //找到运行中的进程PID，
   使用
   #gdb execFile PID    
bt n(next)往下走是看不到已经运行完的错误的，所以就谈到bt（backtrace）命令——回溯。
info line main  //查看main的信息
   info line 0x...  //查看某一行信息
r是run的缩写     r 参数      以参数运行程序
quit,退出gdb调试
gdb -q 程序名      //这个操作可以不输出一些信息（gdb的一些版本信息说明之类的）   
gdb也支持运行linux命令的，可以在gdb的提示符中，输入shell，然后在输入你需要的命令就可以
了。例如：shell clear     清屏
b*0x...            //在逆向调试的时候，在某行指令下断点必须遵照这个格式  
x/i 可以查看指令
        例如： x/15i main  查看main函数中的第15条指令  
 x/43bc 0xffffd190 指的是 0xffffd190后43个内存单元
 
想边看汇编变调试就先：r 参数    ，然后使用layout asm，直接动态显示指令运行
       layout 几个参数：
               src   : Displays source and command windows.
               asm   : Displays disassembly and command windows.
               split : Displays source, disassembly and command windows.
               regs  : Displays register window. If existing layout
       c（continue）  可以让程序执行到下一个断点处
       p $eax   查看寄存器的值
       x/i $pc  查看当前指令的运行地址
修改寄存器值的两种方式(想要满足某个比较条件直接修改寄存器，可以跳到想跳的地方)：
      1)直接来：
               set $eax=value
      2)找到寄存器的地址通过这个地址修改值：
               p $rsp+0x714
               set *上一步的值=value      
x/  <n/f/u>  <addr>   //内存地址中的值，x即examine,3个参数顺序可变
     
   1)n是一个正整数，表示需要显示的内存单元的个数
   2)f表示显示的格式（有以下选项）：
       x （hexadecimal）按十六进制格式显示变量。 
       d （signed decimal）按十进制格式显示变量。 
       u （unsigned decimal）按十进制格式显示无符号整型。 
       o （octal）按八进制格式显示变量。 
       t （binary）按二进制格式显示变量。 
       a （address）按十六进制格式显示地址，并显示距离前继符号的偏移量(offset)。常用于定位未知 地址(变量)。 
       c （character）按字符格式显示变量。 
       f （floating）按浮点数格式显示变量。  
   3)u表示从当前地址往后请求的字节数单位，如果不指定的话，GDB默认是4个bytes：
       b表示单字节，
       h表示双字节，
       w表示四字节，
       g表示八字节   
x/10x $sp-->打印stack的前10个元素   
reverse-stepi   //回退一条指令
info thread   // 查看所有线程

continue         执行到下一暂停点或程序结束。
next         执行一行源代码但不进入函数内部。
step        执行一行源代码而且进入函数内部。
gdb 运行程序
例子程序名为prog，则在终端输入 gdb prog
gdb 设置参数
set args 可指定运行时参数。（如：set args 10 20 30 40 50） 
show args 命令可以查看设置好的运行参数。 
若要再次修改参数，可再执行一遍 set args
运行
输入 r 运行 
出错后，输入 bt 查看运行堆栈
退出
输入 quit
