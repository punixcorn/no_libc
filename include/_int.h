#ifndef __INT_H
#define __INT_H

/* int types */
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;
typedef unsigned int uint_t;

/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
#ifndef __intptr_t_defined
typedef long int intptr_t;
#define __intptr_t_defined
#endif
typedef unsigned long int uintptr_t;
#else
#ifndef __intptr_t_defined
typedef int intptr_t;
#define __intptr_t_defined
#endif
typedef unsigned int uintptr_t;
#endif

/* Largest integral types.  */
#if __WORDSIZE == 64
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
#else
__extension__ typedef long long int intmax_t;
__extension__ typedef unsigned long long int uintmax_t;
#endif

/* Minimum of signed integral types.  */
#define INT8_MIN (-128)
#define INT16_MIN (-32767 - 1)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN (-__INT64_C(9223372036854775807) - 1)
/* Maximum of signed integral types.  */
#define INT8_MAX (127)
#define INT16_MAX (32767)
#define INT32_MAX (2147483647)
#define INT64_MAX (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
#define UINT8_MAX (255)
#define UINT16_MAX (65535)
#define UINT32_MAX (4294967295U)
#define UINT64_MAX (__UINT64_C(18446744073709551615))

/* Minimum of signed integral types having a minimum size.  */
#define INT_LEAST8_MIN (-128)
#define INT_LEAST16_MIN (-32767 - 1)
#define INT_LEAST32_MIN (-2147483647 - 1)
#define INT_LEAST64_MIN (-__INT64_C(9223372036854775807) - 1)

/* Maximum of signed integral types having a minimum size.  */
#define INT_LEAST8_MAX (127)
#define INT_LEAST16_MAX (32767)
#define INT_LEAST32_MAX (2147483647)
#define INT_LEAST64_MAX (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types having a minimum size.  */
#define UINT_LEAST8_MAX (255)
#define UINT_LEAST16_MAX (65535)
#define UINT_LEAST32_MAX (4294967295U)
#define UINT_LEAST64_MAX (__UINT64_C(18446744073709551615))

/* Values to test for integral types holding `void *' pointer.  */
#if __WORDSIZE == 64
#define INTPTR_MIN (-9223372036854775807L - 1)
#define INTPTR_MAX (9223372036854775807L)
#define UINTPTR_MAX (18446744073709551615UL)
#else
#define INTPTR_MIN (-2147483647 - 1)
#define INTPTR_MAX (2147483647)
#define UINTPTR_MAX (4294967295U)
#endif

/* Minimum for largest signed integral type.  */
#define INTMAX_MIN (-__INT64_C(9223372036854775807) - 1)
/* Maximum for largest signed integral type.  */
#define INTMAX_MAX (__INT64_C(9223372036854775807))

/* Maximum for largest unsigned integral type.  */
#define UINTMAX_MAX (__UINT64_C(18446744073709551615))

#endif
