#include "../include/_lib.h"

#include "../include/_syscalls.h"

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
#include "../include/main.h"
void _start() {
    int main_return = main();
    _exit(main_return);
}

// will use brk / sbrk later
void* brk();
void* sbrk();

// malloc using mmap
void* _malloc(size_t size) {
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

/* mmap syscall
void * _mmap(size_t size){
    void * ptr = null;
    __asm__ inline(
    "mov $0, %%r9;" // offset
    "mov $0, %%r8;" // file descriptor
    "mov $34,%%r10;" // MAP_PRIVATE || MAP_SHARED
    "movq $0, %%rdi;" // mapp destination (void addr)
    "movq $3 , %%rdx;" // PROT_READ || PROT_WRITE
    "syscall;"
    "mov %%rax, %[return_ptr];"
    : [return_ptr]"=rm"(ptr)
    : "S"(size),"a"(SYSMMAP)
    );
    return ptr;
}
*/
#ifdef __DEV_
void _free(void* ptr) {
    __asm__ inline(
        "movq $0,%%rbx;"
        "movq %%rbx,%0"
        : "=r"(ptr));
}

#endif
