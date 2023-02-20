// Lauf-LED's, Angabe
//
// Aufruf: leds
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sdlinterf.h"

// Anzahl der LED's (Zeilen und Spalten)
#define ANZAHL 14
// Verzögerung pro Verschiebung (Millisekunden)
#define VERZ 100

typedef unsigned int uint;

// Bekommt eine LED-Zeile als Parameter
// und liefert sie um 1 LED nach links rotiert als Return-Wert
int rotate(int z, bool isMirror)
{
  if (isMirror) {
    uint result = 0;
    for (uint i = 0, j = 14; i < 7; i++, j -= 2) {
      result |= (z & (1 << i)) << j;
      result |= (z & (1 << (14 - i))) >> j;
    }
    return result;
  }

  return ((z & 1) << 14) |    // bit 0 wandert an Stelle 14
    ((z & 0x00000100) >> 2) | // bit 9 wandert an bit 7, da 8 nicht belegt
    ((z & 0x00007E7E) >> 1);  // alle anderen wandern 1 nach rechts
}

int main(int argc, char **argv)
{
  // Darzustellendes Muster:
  // Zeilenweise von oben nach unten: 1 Array-Element = 1 Zeile
  // 2 mal 7 Bit (Bit 0-6 und Bit 8-14) von links nach rechts:
  // Bit 0 ... ganz rechts, Bit 14 ... ganz links
  // (Bit 7 und Bit 15-31: unbenutzt)
  // 0-Bit ... LED aus, 1-Bit ... LED ein
  int data[] = {
    0x0C00, 0x1E00, 0x3300, 0x3300, 0x6140, 0x6140, 0x6140,
    0x4061, 0x4061, 0x4061, 0x0033, 0x0033, 0x001E, 0x000C };

  // Größe des Platzes einer LED in Pixeln         
  int feldgr = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 1;
  feldgr /= ANZAHL;
  // x- und y-Koordinaten des Mittelpunktes der links oberen LED     
  int links = (SDL_X_SIZE - feldgr * (ANZAHL - 1)) / 2;
  int oben = (SDL_Y_SIZE - feldgr * (ANZAHL - 1)) / 2;

  sdlInit();
  sdlSetFullscreen();

  for (;;) {
    sdlSetBlack();  // Lösche die vorige Anzeige
    
    for (int zeile = 0; zeile < ANZAHL; ++zeile) {
      // Bitmaske: Welches Bit in data entspricht der aktuellen Spalte?
      int maske = 0x4000;   // Bit, das der ersten (linken) Spalte entspricht
      for (int spalte = 0; spalte < ANZAHL; ++spalte) {
        if ((data[zeile] & maske) != 0) {
          // 1-Bit ==> LED leuchtet
          // x-Wert Mittelpunkt je nach Spalte
          // y-Wert Mittelpunkt je nach Zeile
          // Radius = Halbe Feldgröße - Rand
          // Farbe grün
          sdlDrawCirc(links + spalte * feldgr,         
                      oben + zeile * feldgr,           
                      feldgr / 2 - 2, feldgr / 2 - 2,  
                      0, 255, 0);                      
        }
        // Schiebe das maske-Bit zur nächsten LED-Spalte
        // überspringe das unbenutzte Bit zwischen den beiden 7er-Gruppen
        if (spalte == 6) maske >>= 2;
        else maske >>= 1;
      }
    }

    sdlUpdate();
    sdlMilliSleep(VERZ);

    // für das nächste Bild: Alle Zeilen rotieren
    for (int zeile = 0; zeile < ANZAHL; ++zeile) {
      data[zeile] = rotate(data[zeile], argc > 1 && argv[1][0] == 'm');
    }
  }

  sdlExit();
  exit(EXIT_SUCCESS);
}
