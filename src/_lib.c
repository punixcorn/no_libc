#include "../include/_lib.h"
#include "../include/_syscalls.h"

void _exit(int errcode){
    __asm__ inline(
            "movl %0 ,%%edi;"
            "xorl %%eax, %%eax;"
            "movl %1, %%eax;"
            "syscall"
            ::"r"(errcode),"r"(SYSEXIT)
            );
}


// will use brk / sbrk later
void * brk();
void * sbrk();

// malloc using mmap 
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
void _free(void * ptr){
    __asm__ inline(
            "movq $0,%%rbx;"
            "movq %%rbx,%0"
            :"=r"(ptr)
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

char * _itoa(int number){
    if ( number == 0 ) {
      return "0\0";
    }

    // highest an int can be is 10 digits ( signed / unsigned )
    const  int MAX_LENGTH= 11;
    char * intstr = (char *)_malloc(MAX_LENGTH);

    //check for negative
    _bool isNeg = false;
    if ( number < 0 ){
        isNeg = true;
    }
    int i = 0;
    while( number != 0 && i < MAX_LENGTH){
      int temp = number % 10;
      intstr[i] = ( temp > 9 ) ? ( temp - 10 ) + 'a' : temp + '0';
      number /= 10;
      i++;
    }

    // fix the negative sign
    if( isNeg == true ){
        intstr[i] = '-';
        i++;
    }

    // fix the null terminator
    intstr[i] = '\0';
    int reverse =  _reverse(intstr,_strlen(intstr));

    if( reverse == -1 ){
        return "-1";
    }

    return intstr;
}
