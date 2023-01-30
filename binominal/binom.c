#include <stdlib.h>
#include <stdio.h>

#define CACHE_SIZE 35

unsigned int count = 0;
unsigned int cache[CACHE_SIZE][CACHE_SIZE];

void get_out() {
    printf("usage: binom.exe n k | n, k E N; 35 > n, k > 0");
    exit(0);
}

unsigned int noverk(unsigned int n, unsigned int k) {
    count++;
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (n >= CACHE_SIZE || k >= CACHE_SIZE) get_out();
    if (!cache[n][k]) {
        cache[n][k] = noverk(n - 1, k - 1) + noverk(n - 1, k);
    }
    return cache[n][k];
}

int main(int argc, char* argv[]) {
    if (argc != 3) get_out();
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n <= 0 || k <= 0) get_out();

    for (int i = 0; i < CACHE_SIZE; i++) {
        for (int j = 0; j < CACHE_SIZE; j++) {
            cache[i][j] = 0;
        }
    }

    unsigned int result = noverk(n, k);
    printf("result: %i\nneeded %i function calls\n", result, count);
    return 0;
}