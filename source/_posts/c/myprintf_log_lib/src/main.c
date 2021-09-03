#include "myprintf.h"
#include "logger.h"

#define MODULE_NAME "[main]"

int main(){
    myprintf("test %c, %d, %s, %f \n",'c',10,"teststrings",10.301);
    myprintf("test %c, %d, %s, %f \n",'c',10,"teststrings",1.21);

    LOG_INF("test information\n");
    LOG_WAR("test information\n");
    LOG_DBG("test information\n");
    return 0;
}
