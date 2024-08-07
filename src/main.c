#include "../include/main.h"

#include "../include/_io.h"
#include "../include/_lib.h"

int main() {
    int* a = (int*)_malloc(sizeof(int) * 3);
    if (a == null) {
        _println("malloc failed");
        return -1;
    }

    for (int i = 0; i < 3; i++) {
        a[i] = i;
    }

    for (int i = 0; i < 3; i++) {
        _printf("a[%d] = %d\n", i, a[i]);
    }

    _free(&a);
    if (a == null) {
        _println("Memory freed");
    } else {
        _println("Memory not freeed");
    }

    int i = 0;
    _scanf("%d", &i);
    _printf("%d is i", i);
    return 0;
}
