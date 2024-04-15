#ifndef __LIB_H
#define __LIB_H

/* DEFINE NULL */
#include "_int.h"
#define null ((void*)0)
#define NULL null
/* using functions to do free didn't work, i am just bad at what i am doing */
#define _free(ptr) \
    ptr = null

#define _assert(condition)\
    if(!(condition)){\
        _print("Assertion failed at line: ");\
        _print("__LINE__\n"); \
        _exit(-1);\
    }

void _exit(int errcode);

/*This is the dev version*/
#ifdef __DEV_
void _free(void * ptr);
#endif

void * _malloc(size_t size);
void * _memset(void * s, int c, size_t n);
void * brk();
void * sbrk();
#endif


