---
title: c binary 相关工具
categories:
- tools
date: 2021/2/8
toc: true # 是否启用内容索引
---

---
### strings 
---
列出bin文件中的字符串
~~~bash
    strings a.out 

    /lib64/ld-linux-x86-64.so.2
    libc.so.6
    puts
    __cxa_finalize
    strcmp
    __libc_start_main
    GLIBC_2.2.5
    _ITM_deregisterTMCloneTable
    __gmon_start__
    _ITM_registerTMCloneTable
    u+UH
    []A\A]A^A_
    cheking passwd!
    ok you got me
    WRONG !
    Usage: <key>
    :*3$"
~~~

---
### 2进制转16进制 
---
1.  vim 中 ：%！xxd   退回二进制： ：%！xxd  -r 
2.  bash shell: xxd a.out > 16.txt

---
### file 
---
~~~bash 
$ file helloworld.riscv
helloworld.riscv: ELF 64-bit LSB executable, UCB RISC-V, version 1 (SYSV), statically linked, with debug_info, not stripped
~~~

---
### readelf 
---
查看程序段信息, [参考文档](https://blog.csdn.net/yfldyxl/article/details/81566279)
~~~bash 
readelf -S a.out   #  -S(section headers),sections 
~~~


---
### addr2line
---
[用法](https://www.jianshu.com/p/c2e2b8f8ea0d)


---
### ELF 操作库ELFIO
---
只需要 include  elfio/elfio.hpp
[doc](https://gitee.com/mirrors/elfio/tree/master/doc)
[gitee](https://gitee.com/mirrors/elfio)
