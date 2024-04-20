#include "../include/main.h"

#include "../include/_io.h"
#include "../include/_lib.h"
int main() {
    int* foo2 = (int*)_mmap(null, 32, PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (((void*)foo2 == MAP_FAILED)) {
        _print("map failed");
    }
    foo2[1] = 1;
    _printf("foo[1]  = %d\n", foo2[1]);
    int a = _munmap(foo2, 32);
    if (foo2 == null) {
        _print("foo2 is null\n");
    }

    if (a < 0) {
        _print("munmap failed\n");
    }
    return 0;
}
