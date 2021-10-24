---
title: 可变参数的使用案例
date: 2021/8、5
categories: c
---

---
### my_printf
---
只需要实现putchar， 就可以基于C语言的可变参数特性，实现printf. 
~~~bash

typedef CHAR8 *VA_LIST;

#define _INT_SIZE_OF(n) ((sizeof (n) + sizeof (UINTN) - 1) &~(sizeof (UINTN) - 1))

#define VA_START(Marker, Parameter) (Marker = (VA_LIST) ((UINTN) & (Parameter) + _INT_SIZE_OF (Parameter)))

#define VA_ARG(Marker, TYPE)   (*(TYPE *) ((Marker += _INT_SIZE_OF (TYPE)) - _INT_SIZE_OF (TYPE)))

#define VA_END(Marker)      (Marker = (VA_LIST) 0)

void putchar(CHAR8 ch){
  IoWrite16(0x3F8, ch);
}

void printdec(INT8 dec)
{
    if(dec==0)
    {
        return;
    }
    printdec(dec/10);
    putchar( (char)(dec%10 + '0'));
}

void printstr(CHAR8* str)
{
    while(*str)
    {
        putchar(*str++);
    }
}

void printhex(INT8 hex)
{
    if(hex==0)
    {
        printstr("0x");
        return;
    }
    printhex(hex/16);
    if(hex < 10)
    {
        putchar((CHAR8)(hex%16 + '0'));
    }
    else
    {
        putchar((CHAR8)(hex%16 - 10 + 'a' ));
    }
}

void xhlumyprint ( CHAR8* fmt, ... )
{
    INT8  vargint = 0;
    CHAR8* vargpch = NULL;
    CHAR8* pfmt = NULL;
    VA_LIST vp;

    VA_START(vp, fmt);
    pfmt = fmt;

    while(*pfmt)
    {
        if(*pfmt == '%')
        {
            switch(*(++pfmt))
            {
                case 's':
                    vargpch = VA_ARG(vp, CHAR8*);
                    printstr(vargpch);
                    break;
                case 'x':
                case 'X':
                    vargint = VA_ARG(vp, INT8);
                    printhex(vargint);
                    break;
                default:
                    break;
            }
            pfmt++;
        }
        else
        {
            putchar(*pfmt++);
        }
    }
    VA_END(vp);
}


void testPirnt(void){
  putchar('c');
  putchar('\n');

  printdec(55);
  printstr("afwefawefa");
  printhex(0xff);
  putchar('\n');

  xhlumyprint("xhlu %x  \n", 0x44);
  xhlumyprint("xhlu %s  \n", "fawefawef");
}
~~~
