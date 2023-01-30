#define n 4
#define k 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void increment(char *number) {
    // number: 0000 -> 0001 -> 0002...
    for (int i = n - 1; i >= 0; i--) {
        if (number[i] != '0' + k - 1) {
            number[i]++;
            break;
        }
        number[i] = '0';
    }
}

void put_combinations(char **array, int length) {
    // current = 0000
    char current[n + 1];
    for (int i = 0; i < n; i++) {
        current[i] = '0';
    }
    current[n] = '\0';

    for (int i = 0; i < length; i++) {
        strcpy(array[i], current);
        increment(current);
    }
}

int count_unique(char *number) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (number[i] == number[j]) {
                // similar digit
                goto end_of_count_unique_for;
            }
        }
        // no similar digits
        count++;
        end_of_count_unique_for:
    }
}

char *get_most_different(char **array, int length) {
    int difference_target = k < n ? k : n;
    int difference_max = -1;
    char *max = NULL;
    for (int i = 0; i < length; i++) {
        char *number = array[i];
        int count = count_unique(number);
        if (difference_target == count) {
            return number;
        }
        if (difference_max < count) {
            difference_max = count;
            max = number;
        }
    }
    return max;
}

void solve(char **array, int length) {
    char *most_different = get_most_different(array, length);

    // guess
    printf("I guess %s\n", most_different);
    printf("How many digits are in the right place? ");
    int right_placed = 0;
    scanf("%d", &right_placed);
    printf("How many of the others are in your number? ");
    int in_number = 0;
    scanf("%d", &in_number);

    // to be continued...
}

int main() {
    int length = (int)pow(k, n);
    char array[length][n + 1];
    for (int i = 0; i < length; i++) {
        char array[i][n + 1];
        for (int j = 0; j < n; j++) {
            array[i][j] = '_';
        }
        array[i][n] = '\0';
    }

    char *pointer[length];
    for (int i = 0; i < length; i++) {
        pointer[i] = &(array[i][0]);
    }

    put_combinations(pointer, length);

    solve(pointer, length);
}