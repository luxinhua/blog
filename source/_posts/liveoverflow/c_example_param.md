---
title: c 函数参数是怎么传递的，整个过程
date: 2021/3/8
categories: liveoverflow
---

---
### 测试源码
---
~~~bash
#include <stdio.h>

int test2(int a, int b , int c, int d , int e){
  printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
  return 0;
}

int test(int a, int b , int c, int d , int e){
  test2(6,7,8,9,10);
  printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
  return 0;
}

int main(int argc,char *argv[]){
    test(1,2,3,4,5);
    return 0;
}
~~~


---
### 调试过程
---
~~~bash
xhlu@BU-build-XHLU /cygdrive/c/Users/xhlu/Desktop/pri_xx/test
$ gdb a.exe
GNU gdb (GDB) (Cygwin 9.2-1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-cygwin".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a.exe...
(gdb) b main.c:16
Breakpoint 1 at 0x10040114b: file main.c, line 16.
(gdb) r
Starting program: /cygdrive/c/Users/xhlu/Desktop/pri_xx/test/a.exe
[New Thread 8624.0xf8]
[New Thread 8624.0x2404]
[New Thread 8624.0x1560]
[New Thread 8624.0x13b0]

Thread 1 "a" hit Breakpoint 1, main (argc=1, argv=0xffffcc60) at main.c:16
16          test(1,2,3,4,5);
(gdb) disassemble
Dump of assembler code for function main:
   0x0000000100401137 <+0>:     push   %rbp
   0x0000000100401138 <+1>:     mov    %rsp,%rbp
   0x000000010040113b <+4>:     sub    $0x30,%rsp
   0x000000010040113f <+8>:     mov    %ecx,0x10(%rbp)
   0x0000000100401142 <+11>:    mov    %rdx,0x18(%rbp)
   0x0000000100401146 <+15>:    callq  0x100401190 <__main>
=> 0x000000010040114b <+20>:    movl   $0x5,0x20(%rsp)
   0x0000000100401153 <+28>:    mov    $0x4,%r9d
   0x0000000100401159 <+34>:    mov    $0x3,%r8d
   0x000000010040115f <+40>:    mov    $0x2,%edx
   0x0000000100401164 <+45>:    mov    $0x1,%ecx
   0x0000000100401169 <+50>:    callq  0x1004010ca <test>
   0x000000010040116e <+55>:    mov    $0x0,%eax
   0x0000000100401173 <+60>:    add    $0x30,%rsp
   0x0000000100401177 <+64>:    pop    %rbp
   0x0000000100401178 <+65>:    retq
End of assembler dump.
(gdb) s
test (a=1, b=2, c=3, d=4, e=5) at main.c:10
10        test2(6,7,8,9,10);
(gdb) l
5         printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
6         return 0;
7       }
8
9       int test(int a, int b , int c, int d , int e){
10        test2(6,7,8,9,10);
11        printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
12        return 0;
13      }
14
(gdb) disassemble
Dump of assembler code for function test:
   0x00000001004010ca <+0>:     push   %rbp              将被调函数的main栈帧栈底地址放入bp寄存器中,此时我们看到的就是函数test的栈帧
   0x00000001004010cb <+1>:     mov    %rsp,%rbp
   0x00000001004010ce <+4>:     sub    $0x30,%rsp
   0x00000001004010d2 <+8>:     mov    %ecx,0x10(%rbp)   将一会要用到的core寄存器压栈 ， ？为什么不把函数参数直接压栈呢，非要用core寄存器 ？
   0x00000001004010d5 <+11>:    mov    %edx,0x18(%rbp)
   0x00000001004010d8 <+14>:    mov    %r8d,0x20(%rbp)
   0x00000001004010dc <+18>:    mov    %r9d,0x28(%rbp)
=> 0x00000001004010e0 <+22>:    movl   $0xa,0x20(%rsp)   如下6/7/8/9参数被放到了 core 寄存器中，0xa 被压入栈中
   0x00000001004010e8 <+30>:    mov    $0x9,%r9d
   0x00000001004010ee <+36>:    mov    $0x8,%r8d
   0x00000001004010f4 <+42>:    mov    $0x7,%edx
   0x00000001004010f9 <+47>:    mov    $0x6,%ecx
   0x00000001004010fe <+52>:    callq  0x100401080 <test2>
   0x0000000100401103 <+57>:    mov    0x20(%rbp),%ecx
   0x0000000100401106 <+60>:    mov    0x18(%rbp),%edx
   0x0000000100401109 <+63>:    mov    0x30(%rbp),%eax
   0x000000010040110c <+66>:    mov    %eax,0x28(%rsp)
   0x0000000100401110 <+70>:    mov    0x28(%rbp),%eax
   0x0000000100401113 <+73>:    mov    %eax,0x20(%rsp)
   0x0000000100401117 <+77>:    mov    %ecx,%r9d
   0x000000010040111a <+80>:    mov    %edx,%r8d
   0x000000010040111d <+83>:    mov    0x10(%rbp),%edx
   0x0000000100401120 <+86>:    lea    0x1ed9(%rip),%rcx        # 0x100403000
   0x0000000100401127 <+93>:    callq  0x1004011a0 <printf>
   0x000000010040112c <+98>:    mov    $0x0,%eax
   0x0000000100401131 <+103>:   add    $0x30,%rsp
   0x0000000100401135 <+107>:   pop    %rbp
   0x0000000100401136 <+108>:   retq
End of assembler dump.
(gdb) s
[New Thread 8624.0x1d34]
test2 (a=6, b=7, c=8, d=9, e=10) at main.c:5
5         printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
(gdb) disassemble
Dump of assembler code for function test2:
   0x0000000100401080 <+0>:     push   %rbp
   0x0000000100401081 <+1>:     mov    %rsp,%rbp
   0x0000000100401084 <+4>:     sub    $0x30,%rsp
   0x0000000100401088 <+8>:     mov    %ecx,0x10(%rbp)
   0x000000010040108b <+11>:    mov    %edx,0x18(%rbp)
   0x000000010040108e <+14>:    mov    %r8d,0x20(%rbp)
   0x0000000100401092 <+18>:    mov    %r9d,0x28(%rbp)
=> 0x0000000100401096 <+22>:    mov    0x20(%rbp),%ecx
   0x0000000100401099 <+25>:    mov    0x18(%rbp),%edx
   0x000000010040109c <+28>:    mov    0x30(%rbp),%eax
   0x000000010040109f <+31>:    mov    %eax,0x28(%rsp)
   0x00000001004010a3 <+35>:    mov    0x28(%rbp),%eax
   0x00000001004010a6 <+38>:    mov    %eax,0x20(%rsp)
   0x00000001004010aa <+42>:    mov    %ecx,%r9d
   0x00000001004010ad <+45>:    mov    %edx,%r8d
   0x00000001004010b0 <+48>:    mov    0x10(%rbp),%edx
   0x00000001004010b3 <+51>:    lea    0x1f46(%rip),%rcx        # 0x100403000
   0x00000001004010ba <+58>:    callq  0x1004011a0 <printf>
   0x00000001004010bf <+63>:    mov    $0x0,%eax
   0x00000001004010c4 <+68>:    add    $0x30,%rsp
   0x00000001004010c8 <+72>:    pop    %rbp
   0x00000001004010c9 <+73>:    retq
End of assembler dump.
(gdb) n
[New Thread 8624.0x24b0]
6, 7, 8, 9, 10
6         return 0;
(gdb) disassemble
Dump of assembler code for function test2:
   0x0000000100401080 <+0>:     push   %rbp
   0x0000000100401081 <+1>:     mov    %rsp,%rbp
   0x0000000100401084 <+4>:     sub    $0x30,%rsp
   0x0000000100401088 <+8>:     mov    %ecx,0x10(%rbp)
   0x000000010040108b <+11>:    mov    %edx,0x18(%rbp)
   0x000000010040108e <+14>:    mov    %r8d,0x20(%rbp)
   0x0000000100401092 <+18>:    mov    %r9d,0x28(%rbp)
   0x0000000100401096 <+22>:    mov    0x20(%rbp),%ecx
   0x0000000100401099 <+25>:    mov    0x18(%rbp),%edx
   0x000000010040109c <+28>:    mov    0x30(%rbp),%eax
   0x000000010040109f <+31>:    mov    %eax,0x28(%rsp)
   0x00000001004010a3 <+35>:    mov    0x28(%rbp),%eax
   0x00000001004010a6 <+38>:    mov    %eax,0x20(%rsp)
   0x00000001004010aa <+42>:    mov    %ecx,%r9d
   0x00000001004010ad <+45>:    mov    %edx,%r8d
   0x00000001004010b0 <+48>:    mov    0x10(%rbp),%edx
   0x00000001004010b3 <+51>:    lea    0x1f46(%rip),%rcx        # 0x100403000
   0x00000001004010ba <+58>:    callq  0x1004011a0 <printf>
=> 0x00000001004010bf <+63>:    mov    $0x0,%eax
   0x00000001004010c4 <+68>:    add    $0x30,%rsp
   0x00000001004010c8 <+72>:    pop    %rbp
   0x00000001004010c9 <+73>:    retq
End of assembler dump.
(gdb) n
7       }
(gdb) l
2
3
4       int test2(int a, int b , int c, int d , int e){
5         printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
6         return 0;
7       }
8
9       int test(int a, int b , int c, int d , int e){
10        test2(6,7,8,9,10);
11        printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
(gdb) disassemble
Dump of assembler code for function test2:
   0x0000000100401080 <+0>:     push   %rbp
   0x0000000100401081 <+1>:     mov    %rsp,%rbp
   0x0000000100401084 <+4>:     sub    $0x30,%rsp
   0x0000000100401088 <+8>:     mov    %ecx,0x10(%rbp)
   0x000000010040108b <+11>:    mov    %edx,0x18(%rbp)
   0x000000010040108e <+14>:    mov    %r8d,0x20(%rbp)
   0x0000000100401092 <+18>:    mov    %r9d,0x28(%rbp)
   0x0000000100401096 <+22>:    mov    0x20(%rbp),%ecx
   0x0000000100401099 <+25>:    mov    0x18(%rbp),%edx
   0x000000010040109c <+28>:    mov    0x30(%rbp),%eax
   0x000000010040109f <+31>:    mov    %eax,0x28(%rsp)
   0x00000001004010a3 <+35>:    mov    0x28(%rbp),%eax
   0x00000001004010a6 <+38>:    mov    %eax,0x20(%rsp)
   0x00000001004010aa <+42>:    mov    %ecx,%r9d
   0x00000001004010ad <+45>:    mov    %edx,%r8d
   0x00000001004010b0 <+48>:    mov    0x10(%rbp),%edx
   0x00000001004010b3 <+51>:    lea    0x1f46(%rip),%rcx        # 0x100403000
   0x00000001004010ba <+58>:    callq  0x1004011a0 <printf>
   0x00000001004010bf <+63>:    mov    $0x0,%eax
=> 0x00000001004010c4 <+68>:    add    $0x30,%rsp
   0x00000001004010c8 <+72>:    pop    %rbp
   0x00000001004010c9 <+73>:    retq
End of assembler dump.
(gdb) n
test (a=1, b=2, c=3, d=4, e=5) at main.c:11
11        printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
(gdb) disassemble
Dump of assembler code for function test:
   0x00000001004010ca <+0>:     push   %rbp
   0x00000001004010cb <+1>:     mov    %rsp,%rbp
   0x00000001004010ce <+4>:     sub    $0x30,%rsp
   0x00000001004010d2 <+8>:     mov    %ecx,0x10(%rbp)
   0x00000001004010d5 <+11>:    mov    %edx,0x18(%rbp)
   0x00000001004010d8 <+14>:    mov    %r8d,0x20(%rbp)
   0x00000001004010dc <+18>:    mov    %r9d,0x28(%rbp)
   0x00000001004010e0 <+22>:    movl   $0xa,0x20(%rsp)
   0x00000001004010e8 <+30>:    mov    $0x9,%r9d
   0x00000001004010ee <+36>:    mov    $0x8,%r8d
   0x00000001004010f4 <+42>:    mov    $0x7,%edx
   0x00000001004010f9 <+47>:    mov    $0x6,%ecx
   0x00000001004010fe <+52>:    callq  0x100401080 <test2>
=> 0x0000000100401103 <+57>:    mov    0x20(%rbp),%ecx
   0x0000000100401106 <+60>:    mov    0x18(%rbp),%edx
   0x0000000100401109 <+63>:    mov    0x30(%rbp),%eax
   0x000000010040110c <+66>:    mov    %eax,0x28(%rsp)
   0x0000000100401110 <+70>:    mov    0x28(%rbp),%eax
   0x0000000100401113 <+73>:    mov    %eax,0x20(%rsp)
   0x0000000100401117 <+77>:    mov    %ecx,%r9d
   0x000000010040111a <+80>:    mov    %edx,%r8d
   0x000000010040111d <+83>:    mov    0x10(%rbp),%edx
   0x0000000100401120 <+86>:    lea    0x1ed9(%rip),%rcx        # 0x100403000
   0x0000000100401127 <+93>:    callq  0x1004011a0 <printf>
   0x000000010040112c <+98>:    mov    $0x0,%eax
   0x0000000100401131 <+103>:   add    $0x30,%rsp
   0x0000000100401135 <+107>:   pop    %rbp
   0x0000000100401136 <+108>:   retq
End of assembler dump.
(gdb) n
1, 2, 3, 4, 5
12        return 0;
(gdb) n
13      }
(gdb) n
main (argc=1, argv=0xffffcc60) at main.c:17
17          return 0;
(gdb) disassemble
Dump of assembler code for function main:
   0x0000000100401137 <+0>:     push   %rbp
   0x0000000100401138 <+1>:     mov    %rsp,%rbp
   0x000000010040113b <+4>:     sub    $0x30,%rsp
   0x000000010040113f <+8>:     mov    %ecx,0x10(%rbp)
   0x0000000100401142 <+11>:    mov    %rdx,0x18(%rbp)
   0x0000000100401146 <+15>:    callq  0x100401190 <__main>
   0x000000010040114b <+20>:    movl   $0x5,0x20(%rsp)
   0x0000000100401153 <+28>:    mov    $0x4,%r9d
   0x0000000100401159 <+34>:    mov    $0x3,%r8d
   0x000000010040115f <+40>:    mov    $0x2,%edx
   0x0000000100401164 <+45>:    mov    $0x1,%ecx
   0x0000000100401169 <+50>:    callq  0x1004010ca <test>
=> 0x000000010040116e <+55>:    mov    $0x0,%eax
   0x0000000100401173 <+60>:    add    $0x30,%rsp
   0x0000000100401177 <+64>:    pop    %rbp
   0x0000000100401178 <+65>:    retq
End of assembler dump.
(gdb)

~~~

使用bt列出函数栈，使用frame n 查看栈帧，就可以看到出问题时候的函数回溯了，很方便
~~~bash
xhlu@bu-build-XHLU /cygdrive/c/Users/xhlu/Desktop/pri_xx/test
$ gdb a.exe
GNU gdb (GDB) (Cygwin 9.2-1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-cygwin".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a.exe...
(gdb) b main.c:3
Breakpoint 1 at 0x100401096: file main.c, line 4.
(gdb) r
Starting program: /cygdrive/c/Users/xhlu/Desktop/pri_xx/test/a.exe
[New Thread 4068.0xbdc]
[New Thread 4068.0x18d8]
[New Thread 4068.0x1664]
[New Thread 4068.0x2610]

Thread 1 "a" hit Breakpoint 1, test2 (a=6, b=7, c=8, d=9, e=10) at main.c:4
4         printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
(gdb) bt
#0  test2 (a=6, b=7, c=8, d=9, e=10) at main.c:4
#1  0x000000010040110a in test (a=1, b=2, c=3, d=4, e=5) at main.c:10
#2  0x0000000100401173 in main (argc=1, argv=0xffffcc60) at main.c:16
(gdb) frame 0
#0  test2 (a=6, b=7, c=8, d=9, e=10) at main.c:4
4         printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
(gdb) disassemble
Dump of assembler code for function test2:
   0x0000000100401080 <+0>:     push   %rbp
   0x0000000100401081 <+1>:     mov    %rsp,%rbp
   0x0000000100401084 <+4>:     sub    $0x30,%rsp
   0x0000000100401088 <+8>:     mov    %ecx,0x10(%rbp)
   0x000000010040108b <+11>:    mov    %edx,0x18(%rbp)
   0x000000010040108e <+14>:    mov    %r8d,0x20(%rbp)
   0x0000000100401092 <+18>:    mov    %r9d,0x28(%rbp)
=> 0x0000000100401096 <+22>:    mov    0x20(%rbp),%ecx
   0x0000000100401099 <+25>:    mov    0x18(%rbp),%edx
   0x000000010040109c <+28>:    mov    0x30(%rbp),%eax
   0x000000010040109f <+31>:    mov    %eax,0x28(%rsp)
   0x00000001004010a3 <+35>:    mov    0x28(%rbp),%eax
   0x00000001004010a6 <+38>:    mov    %eax,0x20(%rsp)
   0x00000001004010aa <+42>:    mov    %ecx,%r9d
   0x00000001004010ad <+45>:    mov    %edx,%r8d
   0x00000001004010b0 <+48>:    mov    0x10(%rbp),%edx
   0x00000001004010b3 <+51>:    lea    0x1f46(%rip),%rcx        # 0x100403000
   0x00000001004010ba <+58>:    callq  0x1004011b0 <printf>
   0x00000001004010bf <+63>:    mov    $0x0,%eax
   0x00000001004010c4 <+68>:    add    $0x30,%rsp
   0x00000001004010c8 <+72>:    pop    %rbp
   0x00000001004010c9 <+73>:    retq
End of assembler dump.
(gdb) frame 1
#1  0x000000010040110a in test (a=1, b=2, c=3, d=4, e=5) at main.c:10
10        test2(6,7,8,9,10);
(gdb) disassemble
Dump of assembler code for function test:
   0x00000001004010ca <+0>:     push   %rbp
   0x00000001004010cb <+1>:     mov    %rsp,%rbp
   0x00000001004010ce <+4>:     sub    $0x40,%rsp
   0x00000001004010d2 <+8>:     mov    %ecx,0x10(%rbp)
   0x00000001004010d5 <+11>:    mov    %edx,0x18(%rbp)
   0x00000001004010d8 <+14>:    mov    %r8d,0x20(%rbp)
   0x00000001004010dc <+18>:    mov    %r9d,0x28(%rbp)
   0x00000001004010e0 <+22>:    movl   $0xc,-0x4(%rbp)
   0x00000001004010e7 <+29>:    movl   $0xa,0x20(%rsp)
   0x00000001004010ef <+37>:    mov    $0x9,%r9d
   0x00000001004010f5 <+43>:    mov    $0x8,%r8d
   0x00000001004010fb <+49>:    mov    $0x7,%edx
   0x0000000100401100 <+54>:    mov    $0x6,%ecx
   0x0000000100401105 <+59>:    callq  0x100401080 <test2>
=> 0x000000010040110a <+64>:    mov    0x20(%rbp),%ecx
   0x000000010040110d <+67>:    mov    0x18(%rbp),%edx
   0x0000000100401110 <+70>:    mov    0x30(%rbp),%eax
   0x0000000100401113 <+73>:    mov    %eax,0x28(%rsp)
   0x0000000100401117 <+77>:    mov    0x28(%rbp),%eax
   0x000000010040111a <+80>:    mov    %eax,0x20(%rsp)
   0x000000010040111e <+84>:    mov    %ecx,%r9d
   0x0000000100401121 <+87>:    mov    %edx,%r8d
   0x0000000100401124 <+90>:    mov    0x10(%rbp),%edx
   0x0000000100401127 <+93>:    lea    0x1ed2(%rip),%rcx        # 0x100403000
   0x000000010040112e <+100>:   callq  0x1004011b0 <printf>
   0x0000000100401133 <+105>:   mov    -0x4(%rbp),%eax
   0x0000000100401136 <+108>:   add    $0x40,%rsp
   0x000000010040113a <+112>:   pop    %rbp
   0x000000010040113b <+113>:   retq
End of assembler dump.
(gdb) frame 2
#2  0x0000000100401173 in main (argc=1, argv=0xffffcc60) at main.c:16
16          int xh = test(1,2,3,4,5);
(gdb) disassemble
Dump of assembler code for function main:
   0x000000010040113c <+0>:     push   %rbp
   0x000000010040113d <+1>:     mov    %rsp,%rbp
   0x0000000100401140 <+4>:     sub    $0x40,%rsp
   0x0000000100401144 <+8>:     mov    %ecx,0x10(%rbp)
   0x0000000100401147 <+11>:    mov    %rdx,0x18(%rbp)
   0x000000010040114b <+15>:    callq  0x1004011a0 <__main>
   0x0000000100401150 <+20>:    movl   $0x5,0x20(%rsp)
   0x0000000100401158 <+28>:    mov    $0x4,%r9d
   0x000000010040115e <+34>:    mov    $0x3,%r8d
   0x0000000100401164 <+40>:    mov    $0x2,%edx
   0x0000000100401169 <+45>:    mov    $0x1,%ecx
   0x000000010040116e <+50>:    callq  0x1004010ca <test>
=> 0x0000000100401173 <+55>:    mov    %eax,-0x4(%rbp)
   0x0000000100401176 <+58>:    mov    $0x0,%eax
   0x000000010040117b <+63>:    add    $0x40,%rsp
   0x000000010040117f <+67>:    pop    %rbp
   0x0000000100401180 <+68>:    retq
End of assembler dump.
~~~


