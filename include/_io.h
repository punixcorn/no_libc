#ifndef __IO_H_
#define __IO_H_
/* base write / read wrappers */

/* INCLUDES */

#include "_file.h"
#include "_lib.h"
#include "_syscalls.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* read count bytes from fd into buf */
void _read(int fd, char* __restrict __buf, unsigned int count);
/* write count bytes of buf into fd */
void _write(int fd, const char* buf, unsigned int count);

/* write str into STDOUT */
void _print(const char* str);
/* write str into STDOUT with a newline */
void _println(const char* str);
/* write formmated output to STDOUT */
void _printf(const char* __restrict __fmt, ...);
__attribute__((__format__(__printf__, 1, 2)));

/* read until newline from STDIN into buf */
void _scanline(char* __restrict __buf);
/* read size bytes from STDIN to buf */
void _scan(char* __restrict __buf, const unsigned int size)
    __attribute__((nonnull(1)));

/* read from STDIN untill whitespace */
char* __readword(char* buf);

/* read formmated output from STDIN */
void _scanf(const char* __restrict __fmt, ...);
__attribute__((nonnull(1), __format__(__printf__, 1, 2)));

/* np */
int _sscanf(const char* __restrict __s, const char* __restrict __format, ...);
__attribute__((nonnull(1), __format__(__printf__, 2, 3)));

/* write formmated output to S */
int _sprintf(char* __restrict __s, char* __restrict __fmt, ...)
    __attribute__((nonnull(1), __format__(__printf__, 2, 3)));

/* return formmated string fmt */
char* _format(char* __restrict __fmt, ...)
    __attribute__((nonnull(1), __format__(__printf__, 1, 2)));

int _snprintf(char* __restrict __s, size_t __maxlen,
              const char* __restrict __format, ...)
    __attribute__((nonnull(1), __format__(__printf__, 3, 4)));

/* write character to stdout */
int _fputc(int __c, FILE* __stream) __attribute__((nonnull(2)));
int _putc(int __c, FILE* __stream) __attribute__((nonnull(2)));
int _putchar(int __c);

/* Read a character from stdin. */
int _fgetc(FILE* __stream) __attribute__((nonnull(1)));
int _getc(FILE* __stream) __attribute__((nonnull(1)));
int _getchar(void);
int _fscanf(FILE* __restrict __stream, const char* __restrict __format, ...)
    __attribute__((nonnull(1), __format__(__printf__, 2, 3)));

#endif
