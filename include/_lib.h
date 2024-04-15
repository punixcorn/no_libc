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

void _exit(int errcode);

/*This is the dev version*/
#ifdef __DEV_
void _free(void* ptr);
#endif

/*
 * ASSERTS
 * ASSERTS ARE MACROS HERE AND NOT FUNCTIONS
 * DUNNO HOW THE STANDARD LIB DOES IT
 * ASSERTS ARE DEFINED UNDER _EXIT() & _ITOA()
 * BECAUSE ASSERT DEPENDS ON ITOA & EXIT
 */
#define _assert(condition)             \
    if (!(condition)) {                \
        _print("Assertion failed!\n"); \
        _print("IN : ");               \
        _print(__FILE__);              \
        _print(" : ");                 \
        _print(__func__);              \
        _print("()\n");                \
        _print("LINE : ");             \
        _print(_itoa(__LINE__));       \
        _print("\n");                  \
        _exit(-1);                     \
    }

#define _throw_assert(message)     \
    _print("Assertion Called!\n"); \
    _print("IN : ");               \
    _print(__FILE__);              \
    _print(" : ");                 \
    _print(__func__);              \
    _print("()\n");                \
    _print("LINE : ");             \
    _print(_itoa(__LINE__));       \
    _print("\n");                  \
    _print("MESSAGE: ");           \
    _print(message);               \
    _print("\n");                  \
    _exit(-1);

#define _assert_info(condition, message) \
    if (!(condition)) {                  \
        _print("Assertion failed!\n");   \
        _print("IN : ");                 \
        _print(__FILE__);                \
        _print(" : ");                   \
        _print(__func__);                \
        _print("()\n");                  \
        _print("LINE : ");               \
        _print(_itoa(__LINE__));         \
        _print("\n");                    \
        _print("MESSAGE: ");             \
        _print(message);                 \
        _print("\n");                    \
        _exit(-1);                       \
    }

void* _malloc(size_t size);
void* _memset(void* s, int c, size_t n);
void* brk();
void* sbrk();
void* _mmap(size_t size);
#endif
