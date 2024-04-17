#include "../include/_io.h"

#include "../include/_arg.h"
#include "../include/_assert.h"
#include "../include/_lib.h"
#include "../include/_string.h"

/* an IO err will exit with -1 */

#define CHECKNULL(buf)                                \
    if (buf == null) {                                \
        _throw_assert(" buffer is null<((void *)0)>") \
    }

void _read(int fd, char *buf, unsigned int count) {
    __asm__ inline("syscall;" : "=S"(buf) : "a"(SYSREAD), "D"(fd), "d"(count));
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
void _scanline(char *buf) {
    CHECKNULL(buf);
    _read(STDIN_FILENO, buf, 1);
    while (*buf) {
        buf++;
        _read(STDIN_FILENO, buf, 1);
        if (*buf == '\n') {
            break;
        }
    }
    *buf = '\0';
}

void _scan(char *buf, const unsigned int size) {
    CHECKNULL(buf);
    int i = 0;
    while (size - 1 > i) {
        _read(STDIN_FILENO, buf, 1);
        buf++;
        i++;
    }
    buf++;
    *buf = '\0';
}

void _printf(const char *fmt, ...) {
    _va_list ap;
    _va_start(ap, fmt);

    size_t len = _strlen(fmt);
    size_t i = 0;

    for (; i < len; i++) {
        if (fmt[i] == '%') {
            i++;
            switch (fmt[i]) {
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
                    _printn(&fmt[i], 1);
                    break;
            }
        } else if (fmt[i] != '\0') {
            _printn(&fmt[i], 1);
        } else if (fmt[i] == '\0') {
            break;
        }
    }
    _va_end(ap);
    _free(fmt);
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

void _scanf(const char *fmt, ...) {
    CHECKNULL(fmt);
    size_t len = _strlen(fmt);

    _va_list ap;
    _va_start(ap, fmt);

    char *input = (char *)_malloc(100);
    CHECKNULL(input);

    // read the whole line
    //_scanline(input);

    size_t i = 0;
    while (i < len) {
        if (fmt[i] == '%') {
            i++;
            switch (fmt[i]) {
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
    _free(input);
}

int _sprintf(char *s, char *fmt, ...);

char *_format(char *fmt, ...);
