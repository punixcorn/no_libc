#include "../include/main.h"

#include "../include/_io.h"
#include "../include/_lib.h"

struct boost {
    void (*run)();
};

void run() {
    int* a = _malloc(12);
    *a = 12;
    *(a + sizeof(int)) = 24;
    _printf("%d %d\n", *a, *(a + sizeof(int)));
}
static struct boost namespace = {.run = run};

int main() {
    namespace.run();
    return 0;
}
