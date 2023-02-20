#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        uint number = atoi(argv[i]);
        uint result = (number & 0xff000000) >> 24 |
            (number & 0x00ff0000) >> 8 |
            (number & 0x0000ff00) << 8 |
            (number & 0x000000ff) << 24;
        printf("%08X -> %08X\n", number, result);
    }
}