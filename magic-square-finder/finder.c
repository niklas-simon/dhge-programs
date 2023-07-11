#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#ifdef __linux__
#include <pthread.h>
#else
#include <windows.h>
#endif

#define IS 0
#define COULD_BE 1
#define IS_NOT 2

int found = 0;
int length = 0;
int length_2 = 0;
int length_4 = 0;
int realsum = 0;

void get_out()
{
        printf("usage: finder.out length");
        exit(0);
}

void print(int **square)
{
        char string[128];
        char *ptr = string;
        for (int i = 0; i < length; i++) {
                for (int j = 0; j < length; j++) {
                        if (j) {
                                *ptr = ' ';
                                ptr++;
                        }
                        ptr += sprintf(ptr, "%2i", square[i][j]);
                }
                *ptr = '\n';
                ptr++;
        }
        *ptr = '\n';
        ptr++;
        *ptr = '\0';
        fputs(string, stdout);
}

int check(int **square)
{
        bool success = true;

        // check rows
        for (int i = 0; i < length; i++) {
                bool is_null = false;
                int sum = 0;
                for (int j = 0; j < length; j++) {
                        sum += square[i][j];
                        if (!square[i][j]) {
                                is_null = true;
                        }
                }
                if (sum > realsum) {
                        return IS_NOT;
                }
                if (sum != realsum) {
                        if (!is_null) {
                                return IS_NOT;
                        }
                        success = false;
                }
        }

        // check cols
        for (int i = 0; i < length; i++) {
                bool is_null = false;
                int sum = 0;
                for (int j = 0; j < length; j++) {
                        sum += square[j][i];
                        if (!square[j][i]) {
                                is_null = true;
                        }
                }
                if (sum > realsum) {
                        return IS_NOT;
                }
                if (sum != realsum) {
                        if (!is_null) {
                                return IS_NOT;
                        }
                        success = false;
                }
        }

        // check main diag
        int sum = 0;
        bool is_null = false;
        for (int i = 0; i < length; i++) {
                sum += square[i][i];
                if (!square[i][i]) {
                        is_null = true;
                }
        }
        if (sum > realsum) {
                return IS_NOT;
        }
        if (sum != realsum) {
                if (!is_null) {
                        return IS_NOT;
                }
                success = false;
        }

        // check secondary diag
        sum = 0;
        is_null = false;
        for (int i = 0; i < length; i++) {
                sum += square[length - i - 1][i];
                if (!square[i][i]) {
                        is_null = true;
                }
        }
        if (sum > realsum) {
                return IS_NOT;
        }
        if (sum != realsum) {
                if (!is_null) {
                        return IS_NOT;
                }
                success = false;
        }

        return success ? IS : COULD_BE;
}

void generate(int **square, bool *available, int x, int y)
{
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
                if (!available[i]) {
                        continue;
                }
                available[i] = false;

                square[x][y] = i + 1;
                switch (check(square)) {
                case IS:
                        print(square);
                        found++;
                        break;
                case COULD_BE:
                        if (!proceed) {
                                break;
                        }
                        generate(square, available, new_x, new_y);
                        break;
                }

                available[i] = true;
        }
        square[x][y] = 0;
}

#ifdef __linux__
void *thread(void *args)
#else
DWORD WINAPI thread(LPVOID args)
#endif
{
        int index = *((int *)(args));
        if (index / length_2 == index % length_2) {
                return;
        }

        int **square = (int **)malloc(length * sizeof(int *));
        for (int i = 0; i < length; i++) {
                square[i] = (int *)malloc(length * sizeof(int));
                if (!square[i]) {
                        fprintf(stderr, "Error while allocating memory: %s",
                                strerror(errno));
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

        available[index / length_2] = false;
        available[index % length_2] = false;
        square[0][0] = (index / length_2) + 1;
        square[1][0] = (index % length_2) + 1;

        generate(square, available, 2, 0);
}

int main(int argc, char **argv)
{
        if (argc != 2) {
                get_out();
        }
        length = atoi(argv[1]);
        if (length < 3) {
                get_out();
        }
        length_2 = length * length;
        length_4 = length_2 * length_2;

        realsum = length * (length_2 + 1) / 2;

#ifdef __linux__
        pthread_t threads[length_4];
#else
        HANDLE threads[length_4];
#endif
        int indices[length_4];

        struct timeval stop, start;
        gettimeofday(&start, NULL);

        /*indices[1] = 1;
        pthread_create(&(threads[1]), NULL, thread, &(indices[1]));
        pthread_join(threads[1], NULL);
        return 0;*/

        for (int i = 0; i < length_4; i++) {
                indices[i] = i;
#ifdef __linux__
                pthread_create(&(threads[i]), NULL, thread, &(indices[i]));
#else
                threads[i] =
                        CreateThread(NULL, 0, thread, &(indices[i]), 0, NULL);
#endif
        }

#ifdef __linux__
        for (int i = 0; i < length_4; i++) {
                pthread_join(threads[i], NULL);
        }
#else
        WaitForMultipleObjects(length_2, threads, TRUE, INFINITE);
#endif

        gettimeofday(&stop, NULL);
        char time[16];
        int diff_s = stop.tv_sec - start.tv_sec;
        int diff_us = stop.tv_usec - start.tv_usec;
        int hours = diff_s / 3600;
        int minutes = (diff_s % 3600) / 60;
        int seconds = diff_s % 60;
        int milliseconds = diff_us / 1000;
        sprintf(time, "%02d:%02d:%02d.%04dh", hours, minutes, seconds,
                milliseconds);
        printf("found %i squares, took %s\n", found, time);
}