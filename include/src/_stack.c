/*
 * THIS FILE IS FOR THE SUPRESSION OF THIS ERROR
 * TO KEEP THE LINKER QUIET
 * DO NOT DELETE OR MODIFY
 * :(.text+0x102): undefined reference to `__stack_chk_fail'
 * collect2: error: ld returned 1 exit status
 */
#include "../_stack.h"

int __stack_chk_fail(void) { return 0; };
