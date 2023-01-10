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

    sdlDrawLine(
        SDL_X_SIZE / 4,      // Anfangs-X-Koordinate, 0 ... SDL_X_SIZE - 1
        SDL_Y_SIZE / 4,      // Anfangs-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
        3 * SDL_X_SIZE / 4,  // End-X-Koordinate, 0 ... SDL_X_SIZE - 1
        3 * SDL_Y_SIZE / 4,  // End-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
        255,                 // Farb-Rot-Anteil, 0 ... 255
        0,                   // Farb-Grün-Anteil, 0 ... 255
        0
    );                  // Farb-Blau-Anteil, 0 ... 255
    sdlDrawLine(
        SDL_X_SIZE / 4,      // Anfangs-X-Koordinate, 0 ... SDL_X_SIZE - 1
        3 * SDL_Y_SIZE / 4,  // Anfangs-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
        3 * SDL_X_SIZE / 4,  // End-X-Koordinate, 0 ... SDL_X_SIZE - 1
        SDL_Y_SIZE / 4,      // End-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
        0,                   // Farb-Rot-Anteil, 0 ... 255
        255,                 // Farb-Grün-Anteil, 0 ... 255
        0
    );                  // Farb-Blau-Anteil, 0 ... 255

    sdlUpdate();          // zeige die gezeichneten Striche wirklich an
    sdlMilliSleep(3000);  // warte vor Beenden des Programms 3 Sekunden 
    sdlExit();            // mach das Grafikfenster wieder zu

    exit(EXIT_SUCCESS);
}