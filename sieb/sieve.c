#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR "usage: sieve.exe limit\nLimit must be a number greather than 0"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf(ERROR);
        return 0;
    }
    int limit = atoi(argv[1]);
    if (limit <= 0) {
        printf(ERROR);
        return 0;
    }
    bool numbers[limit];
    for (int i = 2; i < limit; i++) {
        numbers[i] = true;
    }
    for (int i = 2; i < limit; i++) {
        for (int j = 2; j * i < limit; j++) {
            numbers[j * i] = false;
        }
    }
    for (int i = 2; i < limit; i++) {
        if (numbers[i]) {
            printf("%i\n", i);
        }
    }
}