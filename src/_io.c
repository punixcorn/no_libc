#include "../include/_io.h"
#include "../include/_string.h"
#include "../include/_arg.h"
#include "../include/_lib.h"


/* an IO err will exit with -1 */

#define CHECKNULL(buf) \
    if( buf  == null ){\
        _throw_assert(" buffer is null<((void *)0)>")\
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
    CHECKNULL(str);
    _write(STDOUT_FILENO,str,_strlen(str));
}

void _printn(const char *str,size_t n){
    CHECKNULL(str);
    _assert_info( n <= _strlen(str),"<size_t>  n  > <size_t> strlen");
    _write(STDOUT_FILENO,str,n);
}

void _println(const char * str ){
    CHECKNULL(str);
    _write(STDOUT_FILENO,str,_strlen(str));
    _write(STDOUT_FILENO,"\n",1);
}

/* buf must be initalized */
void _scanline(char * buf){
    CHECKNULL(buf);
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
    CHECKNULL(buf);
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

     _va_list ap;
     _va_start(ap,fmt);

    unsigned int len  = _strlen(fmt);
    unsigned int i = 0;

    for( ; i < len; i++ ){
        if( fmt[i] == '%' ){
            i++;
            switch(fmt[i]){
                case 'd':
                    //_println("%d found");
                    _print(_itoa(_va_arg(ap,int)));
                      break;
                case 'c':
                    //_println("%c found");
                    char temp = (char)_va_arg(ap,int);
                    _printn(&temp,1);
                      break;
                case 's':
                    //_println("%s found");
                    _print(_va_arg(ap,char *));
                      break;
                case 'l':
                    //_println("%l found");
                    _print(_itoa(_va_arg(ap,long)));
                      break;
                default: 
                    // _println("invalid arg after %");
                   _printn(&fmt[i],1);
                      break;
                  
            }
        }else if ( fmt[i] != '\0' ){
            _printn(&fmt[i],1);
        }else if(fmt[i] == '\0'){
             break;
        }
    }
    _va_end(ap);
    _free(fmt);
}

void _scanf(const char * fmt,...){

}
