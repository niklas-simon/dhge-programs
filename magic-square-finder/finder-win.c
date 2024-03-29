#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <windows.h>

#define IS 0
#define COULD_BE 1
#define IS_NOT 2

int found = 0;
int length = 0;
int length_2 = 0;
int realsum = 0;

void get_out() {
    printf("usage: finder.out length");
    exit(0);
}

void print(int **square) {
    char string[1024];
    char *ptr = string;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (j) {
                ptr += sprintf(ptr, " ");
            }
            ptr += sprintf(ptr, "%2i", square[i][j]);
        }
        ptr += sprintf(ptr, "\n");
    }
    ptr += sprintf(ptr, "\n");
    fputs(string, stdout);
}

bool check(int **square) {
    // check rows and cols
    for (int i = 0; i < length; i++) {
        int rowsum = 0;
        int colsum = 0;
        for (int j = 0; j < length; j++) {
            rowsum += square[i][j];
            colsum += square[j][i];
        }
        if (rowsum != realsum || colsum != realsum) {
            return false;
        }
    }

    // check diags
    int mainsum = 0;
    int secsum = 0;
    for (int i = 0; i < length; i++) {
        mainsum += square[i][i];
        secsum += square[length - i - 1][i];
    }
    if (mainsum != realsum || secsum != realsum) {
        return false;
    }

    return true;
}

void generate(int **square, bool *available, int x, int y) {
    bool proceed = true;
    int new_x = x + 1;
    int new_y = y;
    if (new_x >= length) {
        new_x = 0;
        new_y++;
        if (new_y >= length) {
            proceed = false;
        }
    }
    for (int i = 0; i < length_2; i++) {
        if (available[i]) {
            available[i] = false;
        } else {
            continue;
        }

        square[x][y] = i + 1;
        if (x + 1 < length || y + 1 < length) {
            if (proceed) {
                generate(square, available, new_x, new_y);
            }
        }
        if (check(square)) {
            print(square);
            found++;
        }
        available[i] = true;
    }
    square[x][y] = 0;
}

DWORD WINAPI thread(LPVOID args) {
    int index = *((int *)(args));

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
    bool *available = (bool *)malloc(length_2 * sizeof(bool));
    for (int i = 0; i < length_2; i++) {
        available[i] = true;
    }

    available[index] = false;
    square[0][0] = index + 1;

    generate(square, available, 1, 0);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        get_out();
    }
    length = atoi(argv[1]);
    if (length < 3) {
        get_out();
    }
    length_2 = length * length;
    realsum = length * (length_2 + 1) / 2;
    
    HANDLE threads[length_2];
    int indices[length_2];

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for (int i = 0; i < length_2; i++) {
        indices[i] = i;
        threads[i] = CreateThread(NULL, 0, thread, &(indices[i]), 0, NULL);
    }

    WaitForMultipleObjects(length_2, threads, TRUE, INFINITE);

    gettimeofday(&stop, NULL);
    printf("found %i squares in %f ms\n", found, (double)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000); 
}