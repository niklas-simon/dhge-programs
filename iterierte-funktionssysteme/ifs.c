#include "sdlinterf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    double x;
    double y;
    int r;
    int g;
    int b;
} punkt;

typedef struct {
    double wert;
    double min_wert;
    double max_wert;
    double schritt;
} koeff;

typedef struct {
    int proz_rot;
    int proz_gruen;
    int proz_blau;
    int dazu_rot;
    int dazu_gruen;
    int dazu_blau;
} farbinfo;

#include "spirale-2.h"

punkt array[ANZAHL];

int new_color(int old_color, int old_weight, int new_weight) {
    int color = (old_color * old_weight) / 100 + new_weight;
    color = color < 0 ? 0 : color > 255 ? 255 : color;
    return color;
}

int main() {
    sdlInit();
    sdlSetFullscreen();
    srand(time(NULL));

    for (;;) {
        int t = time(NULL);
        for (int i = 0; i < GL_ANZ; i++) {
            for (int j = 0; j < 6; j++) {
                c[i][j].wert += c[i][j].schritt;
                if (c[i][j].wert < c[i][j].min_wert || c[i][j].wert > c[i][j].max_wert) {
                    c[i][j].schritt *= -1;
                }
            }
        }

        sdlSetBlack();
        double 
            x_min =  1e300, 
            x_max = -1e300, 
            y_min =  1e300, 
            y_max = -1e300;

        array[0] = (punkt){0, 0, ROT, GRUEN, BLAU};

        for (int i = 1; i < ANZAHL; i++) {
            int r = rand() % 100;
            int n = 0;
            for (; n < sizeof(prozent); n++) {
                if (prozent[n] > r) break;
            }

            array[i] = (punkt) {
                c[n][0].wert * array[i - 1].x + c[n][1].wert * array[i - 1].y + c[n][2].wert,
                c[n][3].wert * array[i - 1].x + c[n][4].wert * array[i - 1].y + c[n][5].wert,
                new_color(array[i - 1].r, farbe[n].proz_rot, farbe[n].dazu_rot),
                new_color(array[i - 1].g, farbe[n].proz_gruen, farbe[n].dazu_gruen),
                new_color(array[i - 1].b, farbe[n].proz_blau, farbe[n].dazu_blau)
            };

            if (i >= ERSTER) {
                if (array[i].x < x_min) {
                    x_min = array[i].x;
                }
                if (array[i].x > x_max) {
                    x_max = array[i].x;
                }
                if (array[i].y < y_min) {
                    y_min = array[i].y;
                }
                if (array[i].y > y_max) {
                    y_max = array[i].y;
                }
            }
        }

        for (int i = ERSTER; i < ANZAHL; i++) {
            double x = array[i].x;
            double y = array[i].y;
            sdlDrawPoint(
                ((x - x_min) / (x_max - x_min)) * (SDL_X_SIZE - 1),
                (1 - (y - y_min) / (y_max - y_min)) * (SDL_Y_SIZE - 1),
                array[i].r, array[i].g, array[i].b
            );
        }
        sdlUpdate();
        sdlMilliSleep(10 - (time(NULL) - t));
    }

    printf("press the any key to continue...\n");
    getc(stdin);
    sdlExit();
}