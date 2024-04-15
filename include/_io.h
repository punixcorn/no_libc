#ifndef __IO_H_
#define __IO_H_

/* INCLUDES */
#include "_syscalls.h"
#include "_lib.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* base write / read wrappers */
void _read(int fd,char * buf,unsigned int count);
void _write(int fd,const char * buf,unsigned int count);
void _print(const char * str);
void _println(const char * str);
void _scanline(char * buf);
void _scan(char * buf, const unsigned int  size);



void _printf(const char * fmt,...);
void _scanf(const char * fmt,...);

#endif
