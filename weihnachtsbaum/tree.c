// Kleines Grafik-Demo-Beispiel: 2 Linien
//
// Aufruf: demo0
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdlib.h>

int main(void)
{
    sdlInit();       // mach das Grafik-Fenster auf
    sdlSetBlack();   // mach alle Pixel schwarz

    sdlDrawCirc(400, 560, 30, 30, 128, 64, 0);
    for (int i = 40; i <= 540; i += 50) {
        sdlDrawCirc(400, i, i / 2, 30, 0, 255, 0);
    }

    sdlUpdate();          // zeige die gezeichneten Striche wirklich an
    sdlMilliSleep(10000);  // warte vor Beenden des Programms 3 Sekunden 
    sdlExit();            // mach das Grafikfenster wieder zu

    exit(EXIT_SUCCESS);
}