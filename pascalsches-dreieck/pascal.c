#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void get_out() {
    printf("usage: pascal.c height\nHeight must be an integer greather than 0 and less than 13");
    exit(0);
}

int fak(int n) {
    if (n <= 1) return 1;
    return n * fak(n - 1);
}

int coefficient(int n, int k) {
    return fak(n) / (fak(k) * fak(n - k));
}

int main(int argc, char* argv[]) {
    if (argc != 2) get_out();
    int height = atoi(argv[1]);
    if (height <= 0 || height >= 13) get_out();

    for (int n = 0; n < height; n++) {
        for (int i = 0; i < (height - n); i++) {
            printf("  ");
        }
        for (int k = 0; k <= n; k++) {
            printf(" %3i", coefficient(n, k));
        }
        printf("\n");
    }
}