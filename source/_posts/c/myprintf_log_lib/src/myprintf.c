#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "myprintf.h"
#include "logger.h"

#define MODULE_NAME "[myprintf]"

void myputchar(int8_t c){
    printf("%c",c);
}

void printint(int dec)
{
    if(0 == dec)
    {
        return;
    }
    printint(dec / 10);
    myputchar(dec % 10 + '0');
}
 
void printstr(char *str)
{
    while(*str)
    {
        myputchar(*str);
        str++;
    }
}
void printfloat(float flt)
{
    int tempint = (int)flt;
    int tempflt = (int)(100000 *(flt - tempint));
 
    if(tempflt % 10 > 5)
    {
        tempflt = tempflt /10 + 1;
    }
    else
    {
        tempflt = tempflt / 10;
    }
 
    printint(tempint);
    myputchar('.');
    printint(tempflt);
}
 
void myprintf(const char *format,...)
{
    va_list ap;
	
    va_start(ap,format);
    while(*format)
    {
        if(*format != '%')
	{
	    myputchar(*format);
	    format++;
	}
	else
	{
	    format++;
	    switch(*format)
	    {
	        case 'c':
		{
		    char val_ch = va_arg(ap,int);
		    myputchar(val_ch);
		    format++;
		    break;
		}
 
		case 'd':
		{
		    int val_int = va_arg(ap,int);
		    printint(val_int);
		    format++;
		    break;
		}
 
		case 's':
		{
		    char * val_str = va_arg(ap,char *);
                    printstr(val_str);
		    format++;
		    break;
		}
 
		case 'f':
		{
		    float val_flt = va_arg(ap,double);
		    printfloat(val_flt);
		    format++;
		    break;
		}
		default :{
		    myputchar(*format);
		    format++;
		}
	    }
	}
    }
    va_end(ap); 
}


