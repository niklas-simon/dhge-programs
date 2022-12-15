#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR "Nutzung: pfak.exe zahl\nZahl muss eine Ganzzahl sein! Das Vorzeichen der Zahl wird ignoriert\n"

bool is_prime(int n) {
    for (int i = 2; i < n / 2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf(ERROR);
        return 0;
    }
    int n = atoi(argv[1]);
    if (n < 0) n *= -1;
    printf("Primfaktoren von %d sind: ", n);
    if (n < 4) {
        printf("%d\n", n);
        return 0;
    }
    bool first = true;
    do {
        for (int i = 2; i <= n; i++) {
            if (is_prime(i) && n % i == 0) {
                int count = 0;
                do {
                    n /= i;
                    count++;
                } while (n % i == 0); 
                if (!first) printf(", ");
                if (first) first = false;
                printf("%d", i);
                if (count > 1) {
                    printf("^%d", count);
                }
                break;
            }
        }
    } while (n != 1);
    printf(".\n");
    return 0;
}