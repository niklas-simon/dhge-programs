#include <stdio.h>
#include <stdlib.h>

void print(int number) {
    if (number < 0) {
        putchar('-');
        number *= -1;
    }
    if (number > 9) print(number / 10);
    putchar('0' + (number % 10));
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        print(atoi(argv[i]));
        printf("\n");
    }
}