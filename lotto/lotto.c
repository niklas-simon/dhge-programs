#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ERROR "Usage: lotto.exe\n"
#define MAX 49
#define AMOUNT 7

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    int numbers[MAX];
    for (int i = 0; i < MAX; i++) {
        numbers[i] = 0;
    }

    for (int i = 0; i < AMOUNT; i++) {
        int number = 0;
        do {
            number = rand() % MAX;
        } while (numbers[number]);
        numbers[number] = 1;
    }

    for (int i = 0; i < MAX; i++) {
        if (numbers[i]) {
            printf("%i ", i + 1);
        }
    }
    printf("\n");
    return 0;
}