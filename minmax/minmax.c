#include <stdlib.h>
#include <stdio.h>

#define ERROR "Nutzung: minmax.exe zahl1 [zahl2 ... zahln] \nZahlen muessen Ganzzahlen sein!\n"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf(ERROR);
        return 0;
    }
    int tmp = atoi(argv[1]);
    int min = tmp, max = tmp, pos_min = 1, pos_max = 1;
    for (int i = 2; i < argc; i++) {
        tmp = atoi(argv[i]);
        if (tmp < min) {
            min = tmp;
            pos_min = i;
        } else if (tmp > max) {
            max = tmp;
            pos_max = i;
        }
    }
    if (min == max) {
        printf("alle Zahlen sind %d und damit gleich gross.", min);
    } else {
        printf("%d (%d. Zahl) ist die kleinste, %d (%d. Zahl) die groesste Zahl der angegebenen Menge.", min, pos_min, max, pos_max);
    }
    return 0;
}