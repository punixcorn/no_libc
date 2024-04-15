#include "../include/_string.h"
#include "../include/_lib.h"

size_t _strlen(const char * buf){   
    if( buf == null ){
        _exit(2);
    }

    size_t count = 0;
    while(*buf != '\0'){
        buf++;
        count++;
    }
    return count;
}
