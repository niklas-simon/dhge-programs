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

int main(int argc, const char *argv[])
{
    sdlInit();       // mach das Grafik-Fenster auf

    double xStart = atof(argv[1]);
    double yStart = atof(argv[2]);
    double xFix = atof(argv[3]);
    double yFix = atof(argv[4]);
    double limit = atof(argv[5]);
    bool isBrot = atoi(argv[6]);
    double zoomStart = atof(argv[7]);
    double zoomFactor = atof(argv[8]);
    double zoomEnd = atof(argv[9]);
    int maxpixel = SDL_X_SIZE > SDL_Y_SIZE ? SDL_Y_SIZE : SDL_X_SIZE;

    for (double zoom = zoomStart; zoom < zoomEnd; zoom += zoomFactor) {
        sdlSetBlack();
        for (int i = 0; i < SDL_X_SIZE; i++) {
            for (int j = 0; j < SDL_Y_SIZE; j++) {
                double x = xStart + 4 * (i - SDL_X_SIZE / 2) / (maxpixel * zoom);
                double y = yStart + 4 * (j - SDL_Y_SIZE / 2) / (maxpixel * zoom);
                double zx, zy, cx, cy;
                if (isBrot) {
                    zx = 0;
                    zy = 0;
                    cx = x;
                    cy = y;
                } else {
                    zx = x;
                    zy = y;
                    cx = xFix;
                    cy = yFix;
                }
                int count;
                for (count = 0; count < limit; count++) {
                    if (zx * zx + zy * zy >= 4) {
                        //sdlDrawCyclicPoint(i, j, count);
                        sdlDrawPoint(i, j, (count >> 16) % 256, (count >> 8) % 256, count % 256);
                        break;
                    }
                    double xpwr = zx * zx - zy * zy; 
                    double ypwr = 2 * zx * zy;
                    zx = cx + xpwr; 
                    zy = cy + ypwr;
                }
            }
        }
        sdlUpdate();
        sdlMilliSleep(100);
    }

    sdlMilliSleep(1000);
    sdlExit();

    exit(EXIT_SUCCESS);
}