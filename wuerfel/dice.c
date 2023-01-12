#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ERROR "Usage: dice.exe\n"
#define GAMES 100000

int count = 1;

int get_rand() {
    int n = rand() % 6;
    return n;
}

int play() {
    count = 1;
    int prev, curr = get_rand();
    do {
        prev = curr;
        curr = get_rand();
        count ++;
    } while (prev || curr);
    return count;
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    int min = -1;
    int max = 0;
    double avg = 0;

    for (int i = 0; i < GAMES; i++) {
        int tries = play();
        if (tries < min || min == -1) {
            min = tries;
        }
        if (tries > max) {
            max = tries;
        }
        avg = (avg * i + tries) / (i + 1);
    }

    printf("min: %i\nmax: %i\navg: %f", min, max, avg);
    return 0;
}