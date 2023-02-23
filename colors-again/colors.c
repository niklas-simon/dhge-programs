#include "sdlinterf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define STEP 1
#define FRAME 20

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static rgb   hsv2rgb(hsv in);

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

void draw(int half_x, int half_y, double maxlen, int rotation) {
    for (int x = 0 - half_x; x < half_x; x++) {
        for (int y = 0 - half_y; y < half_y; y++) {
            double h = atan(y / (x ? x : 1e-100)) * 180 / 3.1415;
            if (x < 0 && y >= 0) {
                h += 180;
            } else if (x < 0 && y < 0) {
                h += 180;
            } else if (x >= 0 && y < 0) {
                h += 360;
            }
            h += rotation;
            while (h > 360) {
                h -= 360;
            }
            
            double len = sqrt(x * x + y * y);
            double ratio = len / maxlen;
            double s = ratio * 2;
            if (s > 1) s = 1;
            double v = 2 - (ratio * 2);
            if (v > 1) v = 1;

            rgb c = hsv2rgb((hsv) {h, s, v});
            sdlDrawPoint(x + half_x, y + half_y, c.r * 255, c.g * 255, c.b * 255);
        }
    }
    sdlUpdate();
}

int main() {
    srand(time(NULL));
    sdlInit();
    //sdlSetFullscreen();

    int half_x = SDL_X_SIZE / 2;
    int half_y = SDL_Y_SIZE / 2;
    double maxlen = sqrt(half_x * half_x + half_y * half_y);

    for (;;) {
        for (int i = 0; i < 360; i += STEP) {
            draw(half_x, half_y, maxlen, i);
        }
        //sdlMilliSleep(20);
    }

    sdlExit();
}