#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void get_out() {
    printf("usage: minmax.exe number1 number2 [...numberX]");
    exit(0);
}

bool minmax(double* array, int length, double* min, double* max) {
    if (length <= 0) return false;
    *min = array[0];
    *max = array[0];

    for (int i = 1; i < length; i++) {
        if (array[i] < *min) {
            *min = array[i];
        }
        if (array[i] > *max) {
            *max = array[i];
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) get_out();
    int length = argc - 1;
    double array[length];
    for (int i = 0; i < length; i++) {
        array[i] = atof(argv[i + 1]);
    }
    double min;
    double max;
    minmax(array, length, &min, &max);
    printf("min: %f\nmax: %f\n", min, max);
}