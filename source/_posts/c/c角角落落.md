---
title: C 的角角落落
date: 2021/3/2
categories: c
---

---
### __asm__ __volatile__("": : :"memory")  // 强制每次都从内存中读取数据，不优化。
---
memory 强制gcc编译器假设RAM所有内存单元均被汇编指令修改，这样cpu中的registers和cache中已缓存的内存单元中的数据将作废。cpu将不得不在需要的时候重新读取内存中的数据。这就阻止了cpu又将registers，cache中的数据用于去优化指令，而避免去访问内存。

1.  __asm__用于指示编译器在此插入汇编语句。
2.  __volatile__用于告诉编译器，严禁将此处的汇编语句与其它的语句重组合优化。即：原原本本按原来的样子处理这这里的汇编。
3.  memory强制gcc编译器假设RAM所有内存单元均被汇编指令修改，这样cpu中的registers和cache中已缓存的内存单元中的数据将作废。cpu将不得不在需要的时候重新读取内存中的数据。这就阻止了cpu又将registers，cache中的数据用于去优化指令，而避免去访问内存。
4.  "":::表示这是个空指令。barrier()不用在此插入一条串行化汇编指令。



---
### section 段的方式访问函数
---

将我需要用到的函数放在 .mywon 段中

~~~c
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef void (*myown_call)(void);

extern myown_call _myown_start;
extern myown_call _myown_end;

#define _init __attribute__((unused, section(".myown")))
#define func_init(func) myown_call _fn_##func _init = func

static void mspec1(void)
{
    write(1, "aha!\n", 5);
}

static void mspec2(void)
{
    write(1, "aloha!\n", 7);
}

static void mspec3(void)
{
    write(1, "hello!\n", 7);
}

func_init(mspec1);
func_init(mspec2);
func_init(mspec3);

/* exactly like below:
static myown_call mc1  __attribute__((unused, section(".myown"))) = mspec1;
static myown_call mc2  __attribute__((unused, section(".myown"))) = mspec2;
static myown_call mc3  __attribute__((unused, section(".myown"))) = mspec3;
*/

void do_initcalls(void)
{
    myown_call *call_ptr = &_myown_start;
    do {
        fprintf (stderr, "call_ptr: %p\n", call_ptr);
        (*call_ptr)();
        ++call_ptr;
    } while (call_ptr < &_myown_end);
}

int main(void)
{
    do_initcalls();
    return 0;
}
~~~