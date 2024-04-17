#include "../include/main.h"

#include "../include/_arg.h"
#include "../include/_assert.h"
#include "../include/_io.h"
#include "../include/_lib.h"
#include "../include/_string.h"

int main() {
    int age = 0;
    char c;
    char *name = _malloc(10);
    _assert(name != null);
    _printf("enter your name and age and a char:\n");
    _scanf("%s %d", &name, &age, &c);
    _printf("enter name is %s and age : %d%c\n", name, age, c);
    return 0;
}
