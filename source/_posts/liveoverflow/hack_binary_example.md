---
title: hack_binary_example
date: 2021/2/7
categories: liveoverflow
---

--- 
### 目的
---
通过修改bin文件，跳过字符串匹配，密码检查。

--- 
### 代码
---

~~~c
#include <stdio.h>    
#include <string.h>    
    
int main(int argc,char* argv[]){    
        if (argc == 2){    
                printf("cheking passwd!\n");    
                if (strcmp("pwd",argv[1]) == 0){    
                        printf("ok you got me\n");    
                }else    
                        printf("WRONG !\n");    
        }else    
                printf("Usage: <key>\n");    
    
        return ;    
} 
~~~
---
### 带参数打开gdb 
---
~~~c
    gdb --args ./a.out pwd
~~~
---
### gdb 检查
--- 
1.  我们通过gdb单步，到strcmp后一步,打开汇编

~~~c
    (gdb) n
    10	                        printf("WRONG !\n");
    (gdb) disassemble 
    Dump of assembler code for function main:
    0x0000555555555169 <+0>:	endbr64 
    0x000055555555516d <+4>:	push   %rbp
    0x000055555555516e <+5>:	mov    %rsp,%rbp
    0x0000555555555171 <+8>:	sub    $0x10,%rsp
    0x0000555555555175 <+12>:	mov    %edi,-0x4(%rbp)
    0x0000555555555178 <+15>:	mov    %rsi,-0x10(%rbp)
    0x000055555555517c <+19>:	cmpl   $0x2,-0x4(%rbp)
    0x0000555555555180 <+23>:	jne    0x5555555551c8 <main+95>
    0x0000555555555182 <+25>:	lea    0xe7b(%rip),%rdi        # 0x555555556004
    0x0000555555555189 <+32>:	callq  0x555555555060 <puts@plt>
    0x000055555555518e <+37>:	mov    -0x10(%rbp),%rax
    0x0000555555555192 <+41>:	add    $0x8,%rax
    0x0000555555555196 <+45>:	mov    (%rax),%rax
    0x0000555555555199 <+48>:	mov    %rax,%rsi
    0x000055555555519c <+51>:	lea    0xe71(%rip),%rdi        # 0x555555556014
    0x00005555555551a3 <+58>:	callq  0x555555555070 <strcmp@plt>
    0x00005555555551a8 <+63>:	test   %eax,%eax
    0x00005555555551aa <+65>:	jne    0x5555555551ba <main+81>
    0x00005555555551ac <+67>:	lea    0xe65(%rip),%rdi        # 0x555555556018
    0x00005555555551b3 <+74>:	callq  0x555555555060 <puts@plt>
    0x00005555555551b8 <+79>:	jmp    0x5555555551d4 <main+107>
 => 0x00005555555551ba <+81>:	lea    0xe65(%rip),%rdi        # 0x555555556026
    0x00005555555551c1 <+88>:	callq  0x555555555060 <puts@plt>
    0x00005555555551c6 <+93>:	jmp    0x5555555551d4 <main+107>
    0x00005555555551c8 <+95>:	lea    0xe5f(%rip),%rdi        # 0x55555555602e
    0x00005555555551cf <+102>:	callq  0x555555555060 <puts@plt>
    0x00005555555551d4 <+107>:	nop
    0x00005555555551d5 <+108>:	nop
    0x00005555555551d6 <+109>:	leaveq 
    0x00005555555551d7 <+110>:	retq   
    End of assembler dump.
~~~
可以看到 strcmp 后，有一句：test   %eax,%eax ，意思是判断eax 是不是0， 并将状态保存到某个寄存器中，后面肯定也会根据状态判断strcmp返回是不是0
~~~c
    (gdb) x/8b 0x00005555555551aa
    0x5555555551aa <main+65>:	117	14	72	-115	61	101	14	0
    (gdb) x/8x 0x00005555555551aa
    0x5555555551aa <main+65>:	0x75	0x0e	0x48	0x8d	0x3d	0x65	0x0e	0x00
    (gdb) 
~~~
test 后就是跳转命令， jne, 查看intel 架构的手册，他就是根据 0x75 来判断是不是相等的，类似ARM中的 cpsv标志位.
~~~c
    0x75 不等
    0x74 相等
~~~

所以目标就是将0x75更换为0x74,通过上下文的数字确定位置。0x75	0x0e 0x48 0x8d 0x3d

---
### 修改16进制文件
--- 
vim 中，执行：%！xxd 可以将二进制转换为十六进制修改。 ：%！xxd -r 返回二进制， 保存
~~~c
    00001120: f30f 1efa 803d e52e 0000 0075 2b55 4883  .....=.....u+UH.
    00001130: 3dc2 2e00 0000 4889 e574 0c48 8b3d c62e  =.....H..t.H.=..
    00001140: 0000 e809 ffff ffe8 64ff ffff c605 bd2e  ........d.......
    00001150: 0000 015d c30f 1f00 c30f 1f80 0000 0000  ...]............
    00001160: f30f 1efa e977 ffff fff3 0f1e fa55 4889  .....w.......UH.
    00001170: e548 83ec 1089 7dfc 4889 75f0 837d fc02  .H....}.H.u..}..
    00001180: 7546 488d 3d7b 0e00 00e8 d2fe ffff 488b  uFH.={........H.
    00001190: 45f0 4883 c008 488b 0048 89c6 488d 3d71  E.H...H..H..H.=q
    000011a0: 0e00 00e8 c8fe ffff 85c0 750e 488d 3d65  ..........u.H.=e
    000011b0: 0e00 00e8 a8fe ffff eb1a 488d 3d65 0e00  ..........H.=e..
    000011c0: 00e8 9afe ffff eb0c 488d 3d5f 0e00 00e8  ........H.=_....
    000011d0: 8cfe ffff 9090 c9c3 0f1f 8400 0000 0000  ................
    000011e0: f30f 1efa 4157 4c8d 3dc3 2b00 0041 5649  ....AWL.=.+..AVI
    000011f0: 89d6 4155 4989 f541 5441 89fc 5548 8d2d  ..AUI..ATA..UH.-
    00001200: b42b 0000 534c 29fd 4883 ec08 e8ef fdff  .+..SL).H.......
    00001210: ff48 c1fd 0374 1f31 db0f 1f80 0000 0000  .H...t.1........
    00001220: 4c89 f24c 89ee 4489 e741 ff14 df48 83c3  L..L..D..A...H..
    00001230: 0148 39dd 75ea 4883 c408 5b5d 415c 415d  .H9.u.H...[]A\A]
    00001240: 415e 415f c366 662e 0f1f 8400 0000 0000  A^A_.ff.........
~~~

---
### 效果
--- 

~~~
    ./a.out fawe
    cheking passwd!
    WRONG !
    
    vim a.out 
    
    ./a.out fawe
    cheking passwd!
    ok you got me
~~~
