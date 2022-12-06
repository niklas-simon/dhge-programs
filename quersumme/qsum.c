#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ERROR "Nutzung: qsum.exe zahl [-r]\nZahl muss eine Ganzzahl größer gleich 0 sein!\n-r - Berechnet wiederholte Quersumme"

int main(int argc, const char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf(ERROR);
        return 0;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        printf(ERROR);
        return 0;
    }
    bool repeating = (argc == 3) && (strcmp(argv[2], "-r") == 0);
    if (argc == 3 && !repeating) {
        printf(ERROR);
        return 0;
    }
    int sum;
    do {
        sum = 0;
        for (; n > 0; n /= 10) sum += n % 10;
        n = sum;
    } while (repeating && sum >= 10);
    printf("%d\n", sum);
}