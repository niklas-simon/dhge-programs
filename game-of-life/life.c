// Kleines Grafik-Demo-Beispiel: 2 Linien
//
// Aufruf: demo0
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, const char *argv[])
{
    double MUTATION = argc == 2 ? atof(argv[1]) : 0;
    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz

    time_t t;
    srand((unsigned)time(&t));

    bool life[WIDTH][HEIGHT];
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            life[i][j] = ((double)rand()) / RAND_MAX < 1 / 2.0;
        }
    }
    sdlUpdate();
    //sdlMilliSleep(100);

    while (true) {
        sdlSetBlack();
        bool copy[WIDTH][HEIGHT];
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                int count = 0;
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int l = j - 1; l <= j + 1; l++) {
                        if (k >= 0 && k < WIDTH && l >= 0 && l < HEIGHT && life[k][l]) {
                            //printf("raising count because %d %d %d", k, l, life[k][l]);
                            count++;
                        }
                    }
                }
                if (count == 3) copy[i][j] = true;
                else if (count < 2 || count > 3) copy[i][j] = false;
                else copy[i][j] = life[i][j];
                //printf("%d, %d: %d, %d, %d\n", i, j, count, life[i][j], copy[i][j]);
            }
        }
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                life[i][j] = copy[i][j] || (MUTATION != 0 && ((double)rand()) / RAND_MAX < 1 / MUTATION);
                if (life[i][j]) sdlDrawPoint(i, j, ((double)rand()) / RAND_MAX * 255, ((double)rand()) / RAND_MAX * 255, ((double)rand()) / RAND_MAX * 255);
            }
        }
        sdlUpdate();
        //sdlMilliSleep(100);
    }

    sdlExit();            // mach das Grafikfenster wieder zu

    exit(EXIT_SUCCESS);
}