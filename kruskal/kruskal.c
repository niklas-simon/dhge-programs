#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sdlinterf.h"

#define POINTLEN 3000

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

typedef struct Point {
    int x;
    int y;
    struct Point *root;
} Point;

typedef struct Line {
    Point *p1;
    Point *p2;
    int length;
} Line;

int get_length(Point p1, Point p2) {
    int x = p2.x - p1.x;
    int y = p2.y - p1.y;
    return sqrt(x * x + y * y);
}

int compare(const void *v1, const void *v2) {
    return ((Line *) v1)->length - ((Line *) v2)->length;
}

int main() {
    srand(time(NULL));

    sdlInit();
    sdlSetFullscreen();
    sdlSetBlack();

    Point points[POINTLEN];
    for (int i = 0; i < POINTLEN; i++) {
        points[i] = (Point) {rand() % (SDL_X_SIZE - 10) + 5, rand() % (SDL_Y_SIZE - 10) + 5, NULL};
        sdlDrawCirc(points[i].x, points[i].y, 3, 3, 255, 255, 255);
    }

    int linelen = 0;
    for (int i = 1; i < POINTLEN; i++) {
        linelen += i;
    }

    Line lines[linelen];
    Line *ptr = lines;
    int index = 0;
    for (int i = 0; i < POINTLEN; i++) {
        for (int j = i + 1; j < POINTLEN; j++, ptr++, index++) {
            *ptr = (Line) {&(points[i]), &(points[j]), get_length(points[i], points[j])};
        }
    }

    qsort(lines, linelen, sizeof(Line), compare);

    int actual = 0;

    for (int i = 0; i < linelen; i++) {
        Line line = lines[i];
        Point *p1root;
        for (p1root = line.p1; p1root->root; p1root = p1root->root) {}
        Point *p2root;
        for (p2root = line.p2; p2root->root; p2root = p2root->root) {}
        if (p1root != p2root) {
            p2root->root = p1root;
            rgb color = hsv2rgb((hsv) {(double)(rand() % 360), 1, 1});
            actual++;
            sdlDrawLine(line.p1->x, line.p1->y, line.p2->x, line.p2->y, color.r * 255, color.g * 255, color.b * 255);
        }
    }

    printf("drawing %i lines", actual);

    sdlUpdate();
    for(;;) {
        sdlMilliSleep(20);
    }
    sdlExit();
}