#ifndef __ASSERT_H_
#define __ASSERT_H_

/*
 * ASSERTS
 * ASSERTS ARE MACROS HERE AND NOT FUNCTIONS
 * DUNNO HOW THE STANDARD LIB DOES IT
 * ASSERTS ARE DEFINED UNDER _EXIT() & _ITOA()
 * BECAUSE ASSERT DEPENDS ON ITOA & EXIT
 */
#define _assert(condition)       \
    if (!(condition)) {          \
        _print(_itoa(__LINE__)); \
        _print(" : ");           \
        _print(__FILE__);        \
        _print(" : ");           \
        _print(__func__);        \
        _print("()\n");          \
        _print("\t[ ");          \
        _print(#condition);      \
        _print(" ] FAILED\n");   \
        _exit(-1);               \
    }

#define _throw_assert(message) \
    _print(_itoa(__LINE__));   \
    _print(" : ");             \
    _print(__FILE__);          \
    _print(" : ");             \
    _print(__func__);          \
    _print("()\n");            \
    _print(message);           \
    _print("\n");              \
    _exit(-1);

#define _static_assert(condition, message) \
    if (!(condition)) {                    \
        _print(_itoa(__LINE__));           \
        _print(" : ");                     \
        _print(__FILE__);                  \
        _print(" : ");                     \
        _print(__func__);                  \
        _print("()\n");                    \
        _print("\t[ ");                    \
        _print(#condition);                \
        _print(" ] FAILED\n");             \
        _print("MESSAGE: ");               \
        _print(message);                   \
        _print("\n");                      \
        _exit(-1);                         \
    }

#endif
