#ifndef __ARG_H_
#define __ARG_H_

/* variadic args */
typedef __builtin_va_list _va_list;
#define _va_start(v, ...) __builtin_va_start(v, 0)
// #define _va_start(v,l)     __builtin_va_start(v,l)
#define _va_end(v) __builtin_va_end(v)
#define _va_arg(v, l) __builtin_va_arg(v, l)

#endif
