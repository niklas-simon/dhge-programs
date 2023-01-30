#include "sdlinterf.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

int xPos = 0;
int yPos = 0;
int orientation = 1000;
int step = 100;
int delay = 10;

int steps[] = {-1, 1, 1, 1, -1, -1, -1, 1};
int step_count = 8;

int colors[9][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {255, 0, 255}, {255, 128, 0}, {0, 255, 128}, {128, 255, 0}};
int color_count = 9;

void get_out() {
    printf("usage: peano.exe depth");
    exit(0);
}

void put_new_coords(int* x, int* y, int orientation, int step) {
    switch (orientation % 4) {
        case 0:
            *x += step;
            *y += step;
            break;
        case 1:
            *x += step;
            *y -= step;
            break;
        case 2:
            *x -= step;
            *y -= step;
            break;
        case 3:
            *x -= step;
            *y += step;
            break;
        default:
            break;
    }
}

void draw(int depth) {
    if (depth == 0) {
        int xOld = xPos;
        int yOld = yPos;
        put_new_coords(&xPos, &yPos, orientation, step);
        sdlDrawLine(xOld, yOld, xPos, yPos, 
            colors[orientation % color_count][0], 
            colors[orientation % color_count][1], 
            colors[orientation % color_count][2]);
        sdlUpdate();
        sdlMilliSleep(delay);
        return;
    }

    draw(depth - 1);
    for (int i = 0; i < step_count; i++) {
        orientation = orientation + steps[i];
        draw(depth - 1);
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 2) get_out();
    int depth = atoi(argv[1]);
    if (depth <= 0) get_out();

    int page = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 1;
    int power = pow(3, depth);
    step = page / power;
    page = step * power;
    xPos = (SDL_X_SIZE - page) / 2;
    yPos = (SDL_Y_SIZE - page) / 2;
    orientation = 1000;
    delay = 1500 / pow(5, depth);

    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz

    draw(depth);

    printf("press ENTER to exit");
    getchar();
}

/*int main(int argc, char* argv[]) {
    if (argc != 2) get_out();
    int depth = atoi(argv[1]);
    if (depth <= 0) get_out();

    int page = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 1;
    int power = pow(3, depth);
    step = page / power;
    page = step * power;
    xPos = (SDL_X_SIZE - page) / 2;
    yPos = (SDL_Y_SIZE - page) / 2;
    delay = 1500 / pow(5, depth);

    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz

    draw(depth);

    printf("press ENTER to exit");
    getchar();
}*/