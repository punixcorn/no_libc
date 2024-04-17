#ifndef __LIB_H
#define __LIB_H

#include "../include/_string.h"

/* DEFINE NULL */
#include "_int.h"
#define null ((void*)0)
#define NULL null
/* using functions to do free didn't work, i am just bad at what i am doing */
#define _free(ptr) ptr = null

typedef uint8_t _bool;

#ifdef bool
#undef bool
#define bool _bool;
#define false 0
#define true 1
#else
#define bool _bool;
#define false 0
#define true 1
#endif

/* calls SYSEXIT syscall with exitcode as exit code */
void _exit(int exitcode);

/* Place holder for Assert macros */
#include "_assert.h"

/*This is the dev version*/
#ifdef __DEV_
void _free(void* ptr);
#endif

/* allocates memory of size (size) */
void* _malloc(size_t size);

/* not implemented */
void* brk();
/* not implemented */
void* sbrk();

/* not implemented */
void* _mmap(size_t size);

#endif
