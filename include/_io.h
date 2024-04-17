#ifndef __IO_H_
#define __IO_H_
/* base write / read wrappers */

/* INCLUDES */
#include "_lib.h"
#include "_syscalls.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* read count bytes from fd into buf */
void _read(int fd, char* buf, unsigned int count);
/* write count bytes of buf into fd */
void _write(int fd, const char* buf, unsigned int count);
/* write str into STDOUT */
void _print(const char* str);
/* write str into STDOUT with a newline */
void _println(const char* str);
/* read until newline from STDIN into buf */
void _scanline(char* buf);
/* read size bytes from STDIN to buf */
void _scan(char* buf, const unsigned int size);
/* write formmated output to STDOUT */
void _printf(const char* fmt, ...);
/* read from STDIN untill whitespace */
char* __readword(char* buf);
/* read formmated output from STDIN */
void _scanf(const char* fmt, ...);
/* write formmated output to S */
int _sprintf(char* s, char* fmt, ...);
/* return formmated string fmt */
char* _format(char* fmt, ...);
#endif
