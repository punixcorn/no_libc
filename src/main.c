#include "../include/main.h"

#include "../include/_file.h"
#include "../include/_io.h"

int main() {
    /* this does not raise warnings with number of arguments */
    _printf("%s %s", "helli;");
    char* s;
    /*  but this does raise warnings with number of arguments */
    _snprintf(s, 10, "%s %s", "hello");

    /*
     * i don't know why?
     * i have given attribute __printf__(...)
     */
    return 0;
}
