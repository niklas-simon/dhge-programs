#include <stdio.h>
#include <stdlib.h>

#define ERROR "Nutzung: power.exe basis exponent\nEs dürfen nicht beide Zahlen 0 sein und der exponent muss eine Ganzzahl sein"

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        printf(ERROR);
        return 0;
    }
    double n = atof(argv[1]);
    int e = atoi(argv[2]);
    if (n == 0 && e == 0) {
        printf(ERROR);
        return 0;
    }
    double result = 1;
    int abs_e = e < 0 ? e * -1 : e;
    for (int i = 0; i < abs_e; i++) result *= n;
    printf("%f", e < 0 ? 1 / result : result);
    return 0; 
}