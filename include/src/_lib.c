#include "../_lib.h"

#include "../_int.h"

void _exit(int exitcode) {
    __asm__ inline(
        "movl %0 ,%%edi;"
        "xorl %%eax, %%eax;"
        "movl %1, %%eax;"
        "syscall" ::"r"(exitcode),
        "r"(SYSEXIT));
}

/*
 * THIS IS USED TO CALL THE MAIN() FUNCTION FROM MAIN.C
 * PASSED INTO _START()
 * RETURN VALUE FROM MAIN() WILL BE PASSED INTO SYSEXIT()
 */
void _start() {
    int main_return = main();
    _exit(main_return);
    __builtin_unreachable();
}

// will use brk / sbrk later
void* brk();
void* sbrk();

// malloc using mmap
[[nodiscard("returns pointer to heap memory")]] void* _malloc(size_t size) {
    void* ptr = null;
    __asm__ inline(
        "mov $0, %%r9;"     // offset
        "mov $0, %%r8;"     // file descriptor
        "mov $34,%%r10;"    // MAP_PRIVATE || MAP_SHARED
        "movq $0, %%rdi;"   // mapp destination (void addr)
        "movq $3 , %%rdx;"  // PROT_READ || PROT_WRITE
        "syscall;"
        "mov %%rax, %[return_ptr];"
        : [return_ptr] "=rm"(ptr)
        : "S"(size), "a"(SYSMMAP));

    return ptr;
}

void* _mmap(void* addr, uint64_t length, int64_t prot, int64_t flags,
            int64_t fd, int64_t offset) {
    void* ptr = null;
    /*
     * rdx = prot
     * r9 = offset
     * r8 = fd
     * r10 = flags
     * rdi =  addr
     * rdx = prot
     * rsi = length
     */

    /*
    __asm__ inline(
        "mov %1, %%r10;"  // flags
        "mov $2, %%r8;"   // fd
        "mov %3,%%r9;"    // offset
        "syscall;"
        "mov %%rax, %[return_ptr];"
        : [return_ptr] "=rm"(ptr)
        : "D"(addr), "S"(length), "d"(prot), "r"(flags), "r"(fd), "r"(OFFSET),
          "a"(SYSMMAP));
    */
    /* no need to use above, most of the stuff are already place in there for us
     */
    __asm__ inline(
        "movq %%rcx,%%r10;"
        "syscall;"
        "mov %%rax, %[return_ptr];"
        : [return_ptr] "=rm"(ptr)
        : "a"(SYSMMAP));
    return ptr;
}

int _munmap(void* addr, uint64_t length) {
    int ret;
    __asm__ inline(
        "syscall;"
        "movl %%eax,%0;"
        "movq $0x0,%1;"
        : "=r"(ret), "=rm"(addr)
        : "a"(SYSMUNMAP));
    return ret;
};

#ifdef __DEV_
void _free(void* ptr) {
    __asm__ inline(
        "movq $0,%%rbx;"
        "movq %%rbx,%0"
        : "=r"(ptr));
}
#endif
