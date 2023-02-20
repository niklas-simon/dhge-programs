#include <stdlib.h>
#include <stdio.h>

void get_out() {
    fprintf(stderr, "usage: print.out b|h number1 [number2 ... numberN]");
    exit(1);
}

void print_bin(int argc, char **argv) {
    for (int i = 2; i < argc; i++) {
        int number = (unsigned int) atoi(argv[i]);
        for (; number;) {
            for (int _ = 0; _ < 4; number <<= 1, _++) {
                putchar('0' + ((number >> (8 * sizeof(int) - 1)) & 1));
            }
            putchar(' ');
        }
        putchar('\n');
    }
}

const char DIGITS[16] = "0123456789ABCDEF";

void print_hex(int argc, char **argv) {
    for (int i = 2; i < argc; i++) {
        int number = (unsigned int) atoi(argv[i]);
        for (int j = 0; j < (2 * sizeof(unsigned int)); j++) {
            int hex = 0;
            for (int k = 0; k < 4; number <<= 1, k++) {
                hex <<= 1;
                hex |= ((number >> (8 * sizeof(int) - 1)) & 1);
            }
            putchar(DIGITS[hex]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc < 3) get_out();
    switch (argv[1][0])
    {
    case 'b':
        print_bin(argc, argv);
        break;
    case 'h':
        print_hex(argc, argv);
        break;
    default:
        get_out();
        break;
    }
}