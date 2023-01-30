#include <stdlib.h>
#include <stdio.h>

void get_out() {
    printf("usage: power.exe a n\na must be a number, n must be an integer.\n");
    exit(0);
}

double power(double a, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / power(a, -n);
    if (n % 2 == 0) return power(a * a, n / 2);
    return a * power(a, n - 1);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        get_out();
    }
    double a = atof(argv[1]);
    double n = atoi(argv[2]);
    printf("%f\n", power(a, n));
    return 0;
}