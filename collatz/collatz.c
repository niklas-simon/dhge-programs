#include <stdlib.h>
#include <stdio.h>

void get_out() {
    printf("usage: collatz.exe limit");
    exit(0);
}

int get_tries(int number) {
    if (number == 1) return 0;
    if (number % 2 == 0) {
        number /= 2;
    } else {
        number = 3 * number + 1;
    }
    return 1 + get_tries(number);
}

int get_tries2(int number) {
    int tries = 0;
    while (number > 1) {
        if (number % 2 == 0) {
            number /= 2;
        } else {
            number = 3 * number + 1;
        }
        tries++;
    }
    return tries;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        get_out();
    }
    int limit = atoi(argv[1]);
    if (limit <= 0) {
        get_out();
    }
    for (int i = 1; i <= limit; i++) {
        printf("%6i: %4i tries\n", i, get_tries2(i));
    }
    return 0;
}