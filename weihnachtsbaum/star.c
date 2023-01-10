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

    for (int i = 5, j = 255; i <= 255, j >= 5; i += 10, j -= 10) {
        sdlDrawLine(140 + j, 300, 400, 40 + i, i, 255, j);
        sdlDrawLine(400 + i, 300, 400, 40 + i, i, 255, j);
        sdlDrawLine(140 + j, 300, 400, 300 + j, i, 255, j);
        sdlDrawLine(400 + i, 300, 400, 300 + j, i, 255, j);
        sdlDrawLine(140 + j, 40 + j, 400 + j, 40 + i, i, 0, j);
        sdlDrawLine(140 + j, 40 + j, 140 + i, 300 + j, i, 0, j);
        sdlDrawLine(400 + i, 300 + i, 400 + j, 40 + i, i, 0, j);
        sdlDrawLine(400 + i, 300 + i, 140 + i, 300 + j, i, 0, j);
        
        sdlUpdate();          // zeige die gezeichneten Striche wirklich an
        sdlMilliSleep(100);  // warte vor Beenden des Programms 3 Sekunden
        //sdlSetBlack();
    }
    
    sdlMilliSleep(5000); // den des Programms 3 Sekunden 
    sdlExit();            // mach das Grafikfenster wieder zu

    exit(EXIT_SUCCESS);
}