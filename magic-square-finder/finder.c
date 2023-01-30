#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_out() {
    printf("usage: finder.exe length");
    exit(0);
}

void print(int length, int square[]) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf(" [");
        for (int j = 0; j < length; j++) {
            printf(" %2i", square[i * length + j]);
        }
        printf(" ]");
    }
    printf(" ]\n");
}

bool check(int length, int square[]) {
    // rows & cols
    int master = length * (length * length + 1) / 2;
    for (int i = 0; i < length; i++) {
        int sum_row = 0;
        bool has_empty_row = false;
        int sum_col = 0;
        bool has_empty_col = false;
        for (int j = 0; j < length; j++) {
            sum_row += square[i * length + j];
            if (!square[i * length + j]) {
                has_empty_row = true;
            }
            sum_col += square[j * length + i];
            if (!square[j * length + i]) {
                has_empty_col = true;
            }
        }
        printf("%2i %2i\n", sum_row, sum_col);
        if ((has_empty_row && sum_row > master) || (!has_empty_row && sum_row != master)) {
            return false;
        }
        if ((has_empty_col && sum_col > master) || (!has_empty_col && sum_col != master)) {
            return false;
        }
    }

    // diagonals
    bool has_empty_1 = false;
    bool has_empty_2 = false;
    int sum_1 = 0;
    int sum_2 = 0;
    for (int i = 0; i < length; i++) {
        sum_1 += square[i * length + i];
        if (!square[i * length + i]) {
            has_empty_1 = true;
        }
        sum_2 += square[(length - i - 1) * length + i];
        if (!square[i * length + i]) {
            has_empty_2 = true;
        }
    }
    printf("%2i %2i\n", sum_1, sum_2);
    if ((has_empty_1 && sum_1 > master) || (!has_empty_1 && sum_1 != master)) {
        return false;
    }
    if ((has_empty_2 && sum_2 > master) || (!has_empty_2 && sum_2 != master)) {
        return false;
    }
    return true;
}

void find(int length, int square[], int index) {
    if (index == length) {
        print(length, square);
        return;
    }
    for (int i = 1; i <= length * length; i++) {
        square[index] = i;
        print(length, square);
        if (check(length, square)) {
            find(length, square, index + 1);
        }
    }
    square[index] = 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) get_out();
    int length = atoi(argv[1]);
    int square[length * length];
    for (int i = 0; i < length * length; i++) {
        square[i] = 0;
    }
    find(length, square, 0);
}