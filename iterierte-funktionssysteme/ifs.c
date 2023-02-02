#include "sdlinterf.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double value;
    double min;
    double max;
    double step;
} Coefficient;

typedef struct {
    int perc_red;
    int perc_green;
    int perc_blue;
    int add_red;
    int add_green;
    int add_blue;
} ColorInfo;

int main() {
    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz

    int x = 0;
    int y = 0;
    for (int i = 0; i < SDL_X_SIZE; i++) {
        for (int j = 0; j < SDL_Y_SIZE; j++) {
            int old_x = x;
            int old_y = y;
            x = c0 * old_x + c1 * old_y + c2;
            y = c3 * old_x + c4 * old_y + c5;
        }
    }

    char input;
    scanf("%c");
    sdlExit();
}