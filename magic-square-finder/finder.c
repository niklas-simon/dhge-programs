#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void get_out() {
    printf("usage: finder.out length");
    exit(0);
}

void print(int **square, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (j) {
                printf(" ");
            }
            printf("%2i", square[i][j]);
        }
        printf("\n");
    }
}

void check(int **square, int length) {
    int realsum = length * (length * length + 1) / 2;
    printf("All sums must be %i...\n", realsum);

    // check rows and cols
    for (int i = 0; i < length; i++) {
        int rowsum = 0;
        int colsum = 0;
        for (int j = 0; j < length; j++) {
            rowsum += square[i][j];
            colsum += square[j][i];
        }
        if (rowsum != realsum) {
            printf("... but the sum of row %i is %i.\n", i, rowsum);
            return;
        }
        if (colsum != realsum) {
            printf("... but the sum of column %i is %i.\n", i, colsum);
            return;
        }
    }

    // check diags
    int mainsum = 0;
    int secsum = 0;
    for (int i = 0; i < length; i++) {
        mainsum += square[i][i];
        secsum += square[length - i - 1][i];
    }
    if (mainsum != realsum) {
        printf("... but the sum of the main diagonal is %i.\n", mainsum);
        return;
    }
    if (secsum != realsum) {
        printf("... but the sum of the secondary diagonal is %i.\n", secsum);
        return;
    }

    printf("... and they oh so definitely are!\n");
}

void generate(int **square, int length) {
    int x = 0; int y = 0;
    for (int i = 1; i <= length * length; i++) {
        square[x][y] = i;
        if (i % length) {
            x = (x + length - 1) % length;
            y = (y + 2) % length;
        } else {
            x = (x + length - 2) % length;
        }
    }

    print(square, length);
    check(square, length);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        get_out();
    }
    int length = atoi(argv[1]);
    if (length < 0 || length % 2 == 0 || length % 3 == 0) {
        get_out();
    }

    int **square = (int **)malloc(length * sizeof(int *));
    for (int i = 0; i < length; i++) {
        square[i] = (int *)malloc(length * sizeof(int));
        if (!square[i]) {
            fprintf(stderr, "Error while allocating memory: %s", strerror(errno));
            exit(errno);
        }
        for (int j = 0; j < length; j++) {
            square[i][j] = 0;
        }
    }

    generate(square, length);
}