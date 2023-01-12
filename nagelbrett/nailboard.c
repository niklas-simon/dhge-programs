#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ERROR "Usage: nailboard.exe rows balls \nNumbers must be whole and greather than 0!\n"

int main(int argc, const char *argv[]) {
    time_t t;
    srand((unsigned)time(&t));
    if (argc != 3) {
        printf(ERROR);
        return 0;
    }
    int rows = atoi(argv[1]);
    int balls = atoi(argv[2]);
    int boxes[rows + 1];
    for (int i = 0; i < rows + 1; i++) {
        boxes[i] = 0;
    }
    for (int i = 0; i < balls; i++) {
        int state = 0;
        for (int j = 0; j < rows; j++) {
            state += rand() % 2;
        }
        boxes[state]++;
    }
    int max = 0;
    for (int i = 0; i < rows + 1; i++) {
        if (boxes[i] > max) {
            max = boxes[i];
        }
    }
    for (int i = 0; i < rows + 1; i++) {
        printf("%10i ", boxes[i]);
        for (int j = 0; j < (double)boxes[i] * 100 / max; j++) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}