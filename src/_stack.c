/*
 * THIS FILE IS FOR THE SUPRESSION OF THIS ERROR
 * TO KEEP THE LINKER QUIET
 * DO NOT DELETE OR MODIFY
 * :(.text+0x102): undefined reference to `__stack_chk_fail'
 * collect2: error: ld returned 1 exit status
 */

#ifndef __STACK_CHK_FAIL__
#define __STACK_CHK_FAIL__
__stack_chk_fail(void){};
#endif
