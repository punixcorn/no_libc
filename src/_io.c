#include "../include/_io.h"
#include "../include/_string.h"

/* an IO err will exit with 2 */

#define checknull(buf) \
    if( buf  == null ){\
        _exit(2);       \
    }

void _read(int fd,char * buf,unsigned int count){
    __asm__ inline(
                "syscall;"
                :"=S"(buf)
                :"a"(SYSREAD),"D"(fd),"d"(count)
            );
}

void _write(int fd,const char * buf,unsigned int count){
    __asm__ inline(
                "syscall;"
                :
                :"a"(SYSWRITE),"D"(fd),"d"(count),"S"(buf)
            );
}

void _print(const char *str){
    checknull(str);
    _write(STDOUT_FILENO,str,_strlen(str));
}

void _println(const char * str ){
    checknull(str);
    _write(STDOUT_FILENO,str,_strlen(str));
    _write(STDOUT_FILENO,"\n",1);
}

/* buf must be initalized */
void _scanline(char * buf){
    checknull(buf);
    _read(STDIN_FILENO,buf,1);
    while (*buf){
        buf++;
        _read(STDIN_FILENO,buf,1);
        if( *buf == '\n' ){
            break;
        }
    }
    *buf = '\0';
}

void _scan(char * buf, const unsigned int size){
    checknull(buf);
    int i  = 0;
    while ( size - 1 > i ){
        _read(STDIN_FILENO,buf,1);
        buf++;
        i++;
    }
    buf++;
    *buf = '\0';
}

void _printf(const char * fmt,...){
    for( unsigned int i = 0; i < _strlen(fmt), i++; ){
        
        switch(fmt[i]){
            case 'd':
                  break;
            default: 
                  break;
        }
    }
}

void _scanf(const char * fmt,...){

}
