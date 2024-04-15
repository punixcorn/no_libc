#include "../include/main.h"

#include "../include/_arg.h"
#include "../include/_io.h"
#include "../include/_lib.h"
#include "../include/_string.h"

/*
 * Everything written so far just to make a silly bootleg printf(...)
 */

int main() {
    int days = 2;
    const char* name = "potato";
    _printf(
        "My name is %s and  i have been writing the code for %d days \n"
        "The reason why every function has an _ is to shut the compiler and "
        "linker up\n"
        "Enjoy this very slow, useless implementation of libc\n",
        name, days);
    return 0;
}
