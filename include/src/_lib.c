#include "../_lib.h"

#include "../_int.h"

void _exit(int exitcode) {
    __asm__ inline(
        "movl %0 ,%%edi;"
        "xorl %%eax, %%eax;"
        "movl %1, %%eax;"
        "syscall" ::"r"(exitcode),
        "r"(SYSEXIT));
    __builtin_unreachable();
}

/*
 * THIS IS USED TO CALL THE MAIN() FUNCTION FROM MAIN.C
 * PASSED INTO _START()
 * RETURN VALUE FROM MAIN() WILL BE PASSED INTO SYSEXIT()
 */
void _start() {
    /* -127 -> 127, No need to use int , char will do */
    signed char main_return = main();
    _exit(main_return);
    __builtin_unreachable();
}

// will use brk / sbrk later
void* brk();
void* sbrk();

void _free(void* __ptr) {
    /* munmap releases pages, but doesn't nullify the pointer */
    /* passing the pointer by refernce and nullifying after munmap it works */
    /* just passing the pointer and nullifying it after munmap doesn't work */
    void* __vp = *(void**)__ptr;
    /* get size from the original first 4 bytes */
    size_t __psize = *((char*)(__vp)-4);
    //_printf("size is %d\n", __psize);
    void* __ret = _munmap(__vp - 4, __psize);
    _static_assert(__ret == null, "_munmap Failed");
    *(void**)__ptr = null;
}

// malloc using mmap
[[nodiscard("returns pointer to heap memory")]] void* _malloc(size_t size) {
    void* ptr = null;
    size += 4; /* extra 4 bytes ( unsigned int ) for size of block */
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
    *(size_t*)(ptr) = size - 4;
    /* [size] -> [malloc'ed chunk] */
    /* | 4B | -> | ...           | */
    return ptr + 4;
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

    __asm__ inline(
        "movq %%rcx,%%r10;"
        "syscall;"
        "mov %%rax, %[return_ptr];"
        : [return_ptr] "=rm"(ptr)
        : "a"(SYSMMAP));
    return ptr;
}

void* _munmap(void* addr, uint64_t length) {
    void* ret;
    __asm__ inline(
        "syscall;"
        "movq %%rax, %%rdi;"
        "movq %%rax, %0"
        : "=rm"(ret)
        : "a"(SYSMUNMAP));
    return ret;
};

