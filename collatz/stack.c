#include <stdio.h>

void dummy(int size) {
    size++;
    printf("%i\n", size);
    dummy(size);
}

int main() {
    dummy(1);
}