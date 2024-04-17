#ifndef __STRING_H_
#define __STRING_H_

#include "_int.h"

/* return size of buf */
size_t _strlen(const char* buf);

/* reverse a string of length (length)*/
int _reverse(char* str, size_t length);

/* converts number into string */
char* _itoa(int number);

/* converts string to number */
int _stoi(const char* str);

/* sets n bytes of s to c */
void* _memset(void* s, int c, size_t n);

/* copy n bytes of src to dest */
void* _memcpy(void* dst, const void* src, unsigned long n);

#endif
