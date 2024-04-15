#include "../include/_string.h"

#include "../include/_int.h"
#include "../include/_lib.h"

size_t _strlen(const char *buf) {
    if (buf == null) {
        _exit(2);
    }

    size_t count = 0;
    while (*buf != '\0') {
        buf++;
        count++;
    }
    return count;
}

int _reverse(char *str, size_t length) {
    if (str == null) {
        return -1;
    }

    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
    return 0;
}

char *_itoa(int number) {
    if (number == 0) {
        return "0\0";
    }

    // highest an int can be is 10 digits ( signed / unsigned )
    const int MAX_LENGTH = 11;
    char *intstr = (char *)_malloc(MAX_LENGTH);

    // check for negative
    _bool isNeg = false;

    if (number < 0) {
        isNeg = true;
        int temp = 0;
        __asm__ inline(
            "movl %1 ,%%eax;"
            "neg %%eax;"
            "movl %%eax, %0;"
            : "=r"(temp)
            : "a"(number));

        number = temp;
    }

    int i = 0;
    while (number != 0 && i < MAX_LENGTH) {
        int temp = number % 10;
        intstr[i] = (temp > 9) ? (temp - 10) + 'a' : temp + '0';
        number /= 10;
        i++;
    }

    // fix the negative sign
    if (isNeg == true) {
        intstr[i] = '-';
        i++;
    }

    // fix the null terminator
    intstr[i] = '\0';
    int reverse = _reverse(intstr, _strlen(intstr));

    if (reverse == -1) {
        return "-1";
    }

    return intstr;
}
