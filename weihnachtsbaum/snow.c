// Kleines Grafik-Demo-Beispiel: 2 Linien
//
// Aufruf: demo0
//
// Klaus Kusche, 2010

#include "sdlinterf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz
    
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < 91; i++) {
        int x = (double)rand() / RAND_MAX * 700 + 50;
        int y = (double)rand() / RAND_MAX * 500 + 50;
        sdlDrawCirc(x , y, 10, 3, 0, 255, 0);
        sdlDrawCirc(x, y, 3, 10, 0, 255, 0);
        sdlUpdate();          // zeige die gezeichneten Striche wirklich an
        sdlMilliSleep(100);  // warte vor Beenden des Programms 3 Sekunden 
    }

    sdlUpdate();          // zeige die gezeichneten Striche wirklich an
    sdlMilliSleep(10000);  // warte vor Beenden des Programms 3 Sekunden 
    sdlExit();            // mach das Grafikfenster wieder zu

    exit(EXIT_SUCCESS);
}