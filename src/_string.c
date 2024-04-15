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

int _reverse(char  * str, size_t length){
    if (str == null){
        return -1;
    }

    int start = 0;
    int end = length - 1;
    while( start < end  ){
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
    return 0; 
}
