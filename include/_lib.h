#ifndef __LIB_H
#define __LIB_H

#include "_string.h"
#include "_syscalls.h"

/* DEFINE NULL */
#include "_int.h"
#define null ((void*)0)
#define NULL null

/* using functions to do free didn't work, i am just bad at what i am doing */
#define _free(ptr) ptr = null

/* boolean type */
typedef uint8_t _bool;
#ifdef bool
#undef bool
#define bool _bool;
#define false 0
#define true 1
#else
#define bool _bool
#define false 0
#define true 1
#endif

/* calls SYSEXIT syscall with exitcode as exit code */
[[noreturn]] void _exit(int exitcode);

/* program entry */
#include "main.h"
__attribute__((force_align_arg_pointer)) extern void _start();

/* Place holder for Assert macros */
#include "_assert.h"

/*This is the dev version*/
#ifdef __DEV_
void _free(void* ptr);
#endif

/* allocates memory of size (size) */
[[nodiscard("returns pointer to heap memory")]] void* _malloc(size_t size);

/* not implemented */
void* brk();
void* sbrk();

/* macros for mmap */
#include "_mmap_defines.h"
typedef long off_t;
void* _mmap(void* addr, uint64_t length, int64_t prot, int64_t flags,
            int64_t fd, int64_t offset);
int _munmap(void* addr, uint64_t length);

#endif
