#include "../include/main.h"

#include "../include/_file.h"
#include "../include/_io.h"

int main(void) {
    int fd = _open("./main.txt", O_WRONLY | O_CREAT);
    if (fd < 0) {
        _print(_format("file %s is %d\n", "main.txt", fd));
    } else {
        _print("file opened\n");
    }
    _write(fd, "this is main\0", 11);
    int closed = _close(fd);
    if (closed < 0) {
        _print(_format("file failed to close  is %d", closed));

    } else {
        _print("file closed\n");
    }
    return 0;
}
