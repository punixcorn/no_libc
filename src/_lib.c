#include "../include/_lib.h"
#include "../include/_syscalls.h"

void _exit(int errcode){
    __asm__ inline(
            "movq %0 ,%%rdi;"
            "xorl %%eax, %%eax;"
            "movl %1, %%eax;"
            "syscall"
            ::"rm"(errcode),"r"(SYSEXIT)
            );
}

// malloc using mmap 
// will use brk / sbrk later
void * brk();
void * sbrk();

void * _malloc(size_t size){
    void * ptr = null;
    __asm__ inline(
            /*
    "mov $0,%%rdi;"
    "mov $0x3,%%rdx;"
    "mov $0x01,%%r10;"
    "mov $0,%%r9;"
    "mov $0,%%r8;"
    */
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
   
/*
    mov $32,%rsi # 4 x 8bytes; size
    mov $9,%rax ; sysmmap
    "mov $0,%%rdi;"
    "mov $0x3,%%rdx;"
    "mov $0x01,%%r10;"
    "mov $0,%%r9;"
    "mov $-1,%%r8;"
    :
    : "S"(size),"a"(SYSMMAP),
*/
    return ptr;
}

#ifdef __DEV_
void _free(void * ptr){
    __asm__ inline(
            "movq $0,%%rbx;"
            "movq %%rbx,%0"
            :"=rm"(ptr)
            );
}
#endif 


void * _memset(void * s, int c, size_t n){
    for( int i = 0; i < n ; i++ ){
        *(int*)s = c ;
        s+=(sizeof(int));
    }
    return s;
}
