#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ERROR "Nutzung: sqrt.exe zahl\nZahl muss größer gleich 0 sein!"
#define MARGIN 0.0000000001

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf(ERROR);
        return 0;
    }
    double original = atof(argv[1]);
    if (original < 0) {
        printf(ERROR);
        return 0;
    }
    double n = original;
    int i;
    for (i = 1; fabs(n * n - original) > MARGIN; i++) {
        n = (original / n + n) / 2;
        printf("%d. Näherungswert: %.15g\n", i, n);
    }
    printf("Ergebnis: %.15g. Es wurden %d Näherungsschritte benötigt\n", n, i - 1);
}