#include <stdlib.h>
#include <stdio.h>

void get_out() {
    printf("usage: primfuck.exe number\nnumber must be an integer");
    exit(0);
}

void print_fuck(int number, int factor) {
    if (factor > number) return;
    if (number % factor) {
        print_fuck(number, factor + 1);
        return;
    }
    number /= factor;
    printf("%i\n", factor);
    print_fuck(number, factor);
}

int main(int argc, char* argv[]) {
    if (argc != 2) get_out();
    int number = atoi(argv[1]);
    if (number < 0) number *= -1;
    print_fuck(number, 2);
}