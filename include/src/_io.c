#include "../_io.h"

#include "../_arg.h"
#include "../_assert.h"
#include "../_lib.h"
#include "../_string.h"

/* an IO err will exit with -1 */
#define CHECKNULL(buf)                                \
    if (buf == null) {                                \
        _throw_assert(" buffer is null<((void *)0)>") \
    }

void _read(int fd, char *__restrict __buf, unsigned int count) {
    __asm__ inline("syscall;"
                   : "=S"(__buf)
                   : "a"(SYSREAD), "D"(fd), "d"(count));
}

void _write(int fd, const char *buf, unsigned int count) {
    __asm__ inline("syscall;" : : "a"(SYSWRITE), "D"(fd), "d"(count), "S"(buf));
}

void _print(const char *str) {
    CHECKNULL(str);
    _write(STDOUT_FILENO, str, _strlen(str));
}

void _printn(const char *str, size_t n) {
    CHECKNULL(str);
    _static_assert(n <= _strlen(str), "<size_t>  n  > <size_t> strlen");
    _write(STDOUT_FILENO, str, n);
}

void _println(const char *str) {
    CHECKNULL(str);
    _write(STDOUT_FILENO, str, _strlen(str));
    _write(STDOUT_FILENO, "\n", 1);
}

/* buf must be initalized */
void _scanline(char *__restrict __buf) {
    CHECKNULL(__buf);
    _read(STDIN_FILENO, __buf, 1);
    while (*__buf) {
        __buf++;
        _read(STDIN_FILENO, __buf, 1);
        if (*__buf == '\n') {
            break;
        }
    }
    *__buf = '\0';
}

void _scan(char *__restrict __buf, const unsigned int size) {
    CHECKNULL(__buf);
    int i = 0;
    while (size - 1 > i) {
        _read(STDIN_FILENO, __buf, 1);
        __buf++;
        i++;
    }
    __buf++;
    *__buf = '\0';
}

void _printf(const char *__restrict __fmt, ...) {
    _va_list ap;
    _va_start(ap, __fmt);

    size_t len = _strlen(__fmt);
    size_t i = 0;

    for (; i < len; i++) {
        if (__fmt[i] == '%') {
            i++;
            switch (__fmt[i]) {
                case 'd':
                    _print(_itoa(_va_arg(ap, int)));
                    break;
                case 'c': {
                    char temp = (char)(_va_arg(ap, int));
                    _printn(&temp, 1);
                    break;
                }
                case 's':
                    _print(_va_arg(ap, char *));
                    break;
                case 'l':
                    _print(_itoa(_va_arg(ap, long)));
                    break;
                default:
                    _printn(&__fmt[i], 1);
                    break;
            }
        } else if (__fmt[i] != '\0') {
            _printn(&__fmt[i], 1);
        } else if (__fmt[i] == '\0') {
            break;
        }
    }
    _va_end(ap);

    //_free(&__fmt);
}

char *__readword(char *buf) {
    if (buf[0] != '\0') {
        buf = "";
    }
    _read(STDIN_FILENO, buf, 1);

    while (buf) {
        if (*buf == '\n' || *buf == ' ' || *buf == '\0') {
            *buf = '\0';
            break;
        }
        buf++;
        _read(STDIN_FILENO, buf, 1);
    }
    return buf;
}

void _scanf(const char *__restrict __fmt, ...) {
    CHECKNULL(__fmt);
    size_t len = _strlen(__fmt);

    _va_list ap;
    _va_start(ap, __fmt);

    char *input = (char *)_malloc(100);
    CHECKNULL(input);

    // read the whole line
    //_scanline(input);

    size_t i = 0;
    while (i < len) {
        if (__fmt[i] == '%') {
            i++;
            switch (__fmt[i]) {
                case 'd': {
                    __readword(input);
                    *(_va_arg(ap, int *)) = _stoi(input);
                    _memset(input, '\0', _strlen(input));
                    break;
                }
                case 's': {
                    __readword(input);
                    _memcpy(*(_va_arg(ap, char **)), input, sizeof(input));
                    _memset(input, '\0', _strlen(input));
                    break;
                }
                case 'c': {
                    char c;
                    _read(STDIN_FILENO, &c, 1);
                    *(_va_arg(ap, char *)) = c;
                    break;
                }
                default:
                    _throw_assert("Invaild argument after %");
                    break;
            }
        }
        i++;
    }
    _va_end(ap);
    //_free(input);
}

int _sprintf(char *__restrict __s, char *__restrict __fmt, ...) {
    _va_list ap;
    _va_start(ap, __fmt);
    size_t len = _strlen(__fmt);
    _assert(len > _strlen(__s));
    size_t i = 0;
    while (i < len) {
        if (__fmt[i] == '%') {
            i++;
            switch (__fmt[i]) {
                case 'l':
                case 'd': {
                    i++;  // thi__s  will removed the letter after the %
                    char *intstr = _itoa(_va_arg(ap, int));
                    while (*intstr != '\0') {
                        *__s = *intstr;
                        intstr++;
                        __s++;
                    }
                } break;
                case 'c': {
                    i++;  // thi__s  will removed the letter after the %
                    char temp = (char)(_va_arg(ap, int));
                    *__s = temp;
                    __s++;
                    break;
                }
                case 's': {
                    i++;  // thi__s  will removed the letter after the %
                    char *strtemp = _va_arg(ap, char *);
                    while (*strtemp != '\0') {
                        *__s = *strtemp;
                        strtemp++;
                        __s++;
                    }
                    break;
                }
                default: {
                    *__s = __fmt[i];
                    __s++;
                    i++;
                } break;
            }
        } else if (__fmt[i] != '\0') {
            *__s = __fmt[i];
            i++;
            __s++;
        } else if (__fmt[i] == '\0') {
            *__s = '\0';
            break;
        }
    }
    _va_end(ap);
    //_free(__fmt);

    if (__s == null) return -1;
    return 0;
};

char *_format(char *__restrict __fmt, ...) {
    size_t count = 0;  // this will reset the string back to its original
                       // pointer will be seen with str++;
    size_t len = _strlen(__fmt);

    _va_list ap;
    _va_start(ap, __fmt);

    char *s = _malloc(_strlen(__fmt) + 200);
    _memset(s, '\0', len);
    _assert(len > _strlen(s));

    size_t i = 0;
    while (i < len) {
        if (__fmt[i] == '%') {
            i++;
            switch (__fmt[i]) {
                case 'l':
                case 'd': {
                    i++;  // this will removed the letter after the %
                    char *intstr = _itoa(_va_arg(ap, int));
                    while (*intstr != '\0') {
                        *s = *intstr;
                        intstr++;
                        s++;
                        count++;
                    }
                } break;
                case 'c': {
                    i++;  // this will removed the letter after the %
                    char temp = (char)(_va_arg(ap, int));
                    *s = temp;
                    s++;
                    count++;
                    break;
                }
                case 's': {
                    i++;  // this will removed the letter after the %
                    char *strtemp = _va_arg(ap, char *);
                    while (*strtemp != '\0') {
                        *s = *strtemp;
                        strtemp++;
                        s++;
                        count++;
                    }
                    break;
                }
                default: {
                    *s = __fmt[i];
                    s++;
                    count++;
                    i++;
                } break;
            }
        } else if (__fmt[i] != '\0') {
            *s = __fmt[i];
            i++;
            s++;
            count++;
        } else if (__fmt[i] == '\0') {
            *s = '\0';
            break;
        }
    }
    _va_end(ap);
    //_free(__fmt);
    return (s - count);
};

#define _sprintf_macro(fmt, ...) _sprintf(fmt, __VA_ARGS__)
// under development
//
int _snprintf(char *__restrict __s, size_t __maxlen,
              const char *__restrict __format, ...) {
    _va_list ap;
    _va_start(ap, __format);
    size_t len = _strlen(__format);
    _assert(len > _strlen(__s));
    _assert(len < __maxlen);
    size_t i = 0;
    while (i < len) {
        if (__format[i] == '%') {
            i++;
            switch (__format[i]) {
                case 'l':
                case 'd': {
                    i++;  // thi__s  will removed the letter after the %
                    char *intstr = _itoa(_va_arg(ap, int));
                    while (*intstr != '\0') {
                        *__s = *intstr;
                        intstr++;
                        __s++;
                    }
                } break;
                case 'c': {
                    i++;  // thi__s  will removed the letter after the %
                    char temp = (char)(_va_arg(ap, int));
                    *__s = temp;
                    __s++;
                    break;
                }
                case 's': {
                    i++;  // thi__s  will removed the letter after the %
                    char *strtemp = _va_arg(ap, char *);
                    while (*strtemp != '\0') {
                        *__s = *strtemp;
                        strtemp++;
                        __s++;
                    }
                    break;
                }
                default: {
                    *__s = __format[i];
                    __s++;
                    i++;
                } break;
            }
        } else if (__format[i] != '\0') {
            *__s = __format[i];
            i++;
            __s++;
        } else if (__format[i] == '\0') {
            *__s = '\0';
            break;
        }
    }
    _va_end(ap);
    //_free(__format);

    if (__s == null) return -1;
    return 0;
};

/* write character to stdout */
int _fputc(int __c, FILE *__stream) { return -1; };
int _putc(int __c, FILE *__stream) { return -1; };

int _putchar(int __c) {
    char __a = (char)__c;
    _assert(((__a > 126) || (__a < 0)));
    _write(STDOUT_FILENO, &__a, 1);
};

/* Read a character from stdin. */
int _fgetc(FILE *__stream) { return -1; };
int _getc(FILE *__stream) { return -1; };

int _getchar(void) {
    char a;
    _read(STDIN_FILENO, &a, 1);
    return (int)a;
};

int _sscanf(const char *__restrict __s, const char *__restrict __format, ...) {
};
int _fscanf(FILE *__restrict __stream, const char *__restrict __format, ...) {};
