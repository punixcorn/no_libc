# nolibc

My poor attempt of rewritting a small portion of libc without libc but syscalls

this is not intended for any use

purely written out of fun

# FILES

## `_io.h`

basic input / ouput functions

### Functions

| Name      | purpose                                         | definition                                                |
| --------- | ----------------------------------------------- | --------------------------------------------------------- |
| _read     | read from file descriptor                       | `void _read(int fd,char * buf,unsigned int count)`        |
| _write    | write into file descriptor                      | `void _write(int fd,const char * buf,unsigned int count)` |
| _print    | write to standard output                        | `void _print(const char * str)`                           |
| _println  | write into standard output but with a newline   | `void _scanline(char * buf)`                              |
| _scanline | read from standard input into buffer            | `void _scan(char * buf, const unsigned int  size)`        |
| _scan     | read size count from standard input into buffer | `void _scan(char * buf, const unsigned int  size)`        |
| _printf   | formatted string into standard output           | `void _printf(const char * fmt,...)`                      |
| _scanf    | formatted input from standard input             | `void _scanf(const char * fmt,...)`                       |

### DEFINES

```c
STDIN_FILENO 0
STDOUT_FILENO 1
STDERR_FILENO 2
```

---

## `_int.h`

Holds int type definitions

### DEFINES

```c
signed long long int int64_t;
unsigned long long int uint64_t;
signed char int8_t;
unsigned char uint8_t;
signed short int16_t;
unsigned short uint16_t;
unsigned int size_t;
unsigned int uint_t;
```

---

## `_lib.h`

a version of the required basic standard lib stuff

### functions

| Name    | purpose                              | definition                                  |
| ------- | ------------------------------------ | ------------------------------------------- |
| _exit   | exit _start() with value             | `void _exit(int errcode)`                   |
| _malloc | allocate memory on the heap          | `void * _malloc(size_t size)`               |
| _memset | set a memory segment to desired data | `void * _memset(void * s, int c, size_t n)` |
| _brk    | not implemented                      | `void * brk()`                              |
| sbrk    | not implemented                      | `void * _mmap(size_t size)`                 |

### Defines

```c
_assert 
null
NULL 
_throw_assert
_assert_info
bool
_bool
true
false
_free
```

---

## `_string.h`

basic funtions for string manipulation

### functions

| Name     | purpose                   | definition                                |
| -------- | ------------------------- | ----------------------------------------- |
| _strlen  | return lenght of a string | `size_t _strlen(const char * buf)`        |
| _reverse | reverse a string          | `int _reverse(char * str, size_t lenght)` |
| _itoa    | convert int to string     | `char * _itoa(int number)`                |

---

## `_arg.h`

definitions for variadic args

### Defines

```c
typedef __builtin_va_list _va_list;
#define _va_start(v, ...) __builtin_va_start(v, 0)
// #define _va_start(v,l)     __builtin_va_start(v,l)
#define _va_end(v) __builtin_va_end(v)
#define _va_arg(v, l) __builtin_va_arg(v, l)
```

## `main.h`

for calling `int main(){}` in main.c

---

## `syscalls.h`

definitions for syscall numbers

```c
SYSREAD 0
SYSWRITE 1
SYSOPEN 2
SYSCLOSE 3
SYSMMAP 9
SYSEXIT 60
```
