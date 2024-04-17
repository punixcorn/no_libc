#ifndef __STRING_H_
#define __STRING_H_

#include "_int.h"

/* return size of buf */
size_t _strlen(const char* buf) __attribute__((nonnull(1)));
;

/* reverse a string of length (length)*/
int _reverse(char* str, size_t length) __attribute__((nonnull(1)));

/* converts number into string */
char* _itoa(int number);

/* converts string to number */
int _stoi(const char* str) __attribute__((nonnull(1)));

/* sets n bytes of s to c */
void* _memset(void* __restrict__ s, int c, size_t n);

/* copy n bytes of src to dest */
void* _memcpy(void* __restrict__ dst, const void* __restrict__ src,
              unsigned long n) __attribute__((nonnull(1, 2)));

/* compare first n bytes for s1 to s2 */
int _memcmp(const void* __restrict__ s1, const void* __restrict__ s2, size_t n)
    __attribute__((nonnull(1, 2)));

#endif
