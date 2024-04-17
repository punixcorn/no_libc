#include "../include/_string.h"

#include "../include/_int.h"
#include "../include/_io.h"
#include "../include/_lib.h"

size_t _strlen(const char *buf) {
    if (buf == null) {
        _exit(-1);
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

int _stoi(const char *str) {
    if (str == null) return 0;

    int sign = 1, base = 0, i = 0;

    // find the first non whitespace , if whitespaces then ignore.
    while (str[i] == ' ') {
        i++;
    }

    // sign of number
    if (str[i] == '-' || str[i] == '+') {
        sign = 1 - 2 * (str[i++] == '-');
    }

    // checking for valid input
    while (str[i] >= '0' && str[i] <= '9') {
        // handling overflow test case
        if (base > INT32_MAX / 10 ||
            (base == INT32_MAX / 10 && str[i] - '0' > 7)) {
            if (sign == 1)
                return INT32_MAX;
            else
                return INT32_MIN;
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

void *_memset(void *__restrict__ s, int c, size_t n) {
    for (int i = 0; i < n; i++) {
        *(int *)s = c;
        s += (sizeof(int));
    }
    return s;
}

void *_memcpy(void *__restrict__ dst, const void *__restrict__ src,
              unsigned long n) {
    if (dst == null) dst = _malloc(n + 1);

    char *d = dst;
    const char *s = src;

    while (n--) *d++ = *s++;
    return dst;
}

int _memcmp(const void *__restrict__ s1, const void *__restrict__ s2,
            size_t n) {
    _assert(s1 != null && s2 != null);
    const char *a = s1;
    const char *b = s2;

    while (n--) {
        if (a[n] != b[n]) return 0;
    }

    return 1;
}
