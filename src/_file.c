#include "../include/_file.h"

#include <sys/cdefs.h>

#include "../include/_syscalls.h"

int _open(const char *pathname, int flags) {
    int fd = 0;
    mode_t mode = S_IRWXU | S_IROTH | S_IRGRP;
    __asm__ inline(
        "syscall;"
        "movl %0,%%eax;"
        : "=r"(fd)
        : "a"(SYSOPEN), "D"(pathname), "S"(flags), "d"(mode));
    if (fd == -1 || fd == 0) {
        return -1;
    }
    return fd;
};

__attribute__((nonnull)) int _creat(const char *pathname, mode_t mode) {
    int fd = 0;
    int flags = O_CREAT | O_WRONLY | O_TRUNC;
    if (mode == 0) mode = S_IRWXU | S_IROTH | S_IRGRP;
    __asm__ inline(
        "syscall;"
        "movl %0,%%eax;"
        : "=r"(fd)
        : "a"(SYSOPEN), "D"(pathname), "S"(flags), "d"(mode));
    if (fd == -1 || fd == 0) {
        return -1;
    }
    return fd;
}

int _openat(int dirfd, const char *pathname, int flags, ...
            /* mode_t mode */);

int _close(int fd) {
    int ret = 0;
    __asm__ inline(
        "syscall;"
        "movl %%eax, %0;"
        : "=r"(ret)
        : "a"(SYSCLOSE), "D"(fd));
    return ret;
}
