// Rahmenprogramm zum grafischen Sortieren
//
// Aufruf: sort-sdl anzahl
//
// Klaus Kusche, 2020

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

#include "sdlinterf.h"

// Verzögerungen (in Millisekunden) für die Grafik-Anzeige
// ... beim Start
#define START_MS 200
// ... am Ende (bevor das Fenster verschwindet)
#define ENDE_MS 3000
// ... bei jedem Vergleich
#define VERGL_MS 5
// ... bei jeder Vertauschung
#define TAUSCH_MS 500

// die Farbwwerte
const int farbe_normal[] = {
    0,
    255,
    0
}; // normaler Balken
const int farbe_vergl[] = {
    255,
    255,
    0
}; // zu vergleichender Balken
const int farbe_tausch[] = {
    255,
    0,
    255
}; // zu vertauschender Balken
const int farbe_schwarz[] = {
    0,
    0,
    0
}; // schwarz (zum Weglöschen)

// Konstanten (in Pixeln) für das Grafik-Layout
// initialisiert in "main", benutzt in "balken"
// Breite eines Balkens
int breite;
// Eine Höhen-Einheit
int hoehe;
// Linker Rand = Startposition des ersten Balkens in X-Richtung
// (gleicher Rand links & rechts,
// damit die Balken im Fenster schön in der Mitte stehen)
int xstart;

// Zähler für die Vergleiche und Vertauschungen
int vergl = 0;
int vertau = 0;

// Zeichne den Balken Nummer i in Farbe farbe
void balken(const int arr[], int i,
    const int farbe[]) {
    int xpos = xstart + i * breite;
    sdlDrawRectFromTo(xpos + 1, SDL_Y_SIZE - 1,
        xpos + breite - 1, SDL_Y_SIZE - arr[i] * hoehe,
        farbe[0], farbe[1], farbe[2]);
    sdlUpdate();
}

// Vergleiche mit farbiger Anzeige und Verzögerung:
// Ist das Element an pos1 kleiner als das Element an pos2? (true / false)
// Da wir das Array mit lauter verschiedenen Elementen initialisieren,
// kommt "gleich" nicht vor!
bool kleiner(const int arr[], int pos1, int pos2) {
    ++vergl;

    balken(arr, pos1, farbe_vergl);
    balken(arr, pos2, farbe_vergl);
    sdlMilliSleep(VERGL_MS);
    balken(arr, pos1, farbe_normal);
    balken(arr, pos2, farbe_normal);

    return (arr[pos1] < arr[pos2]);
}

// Vertausche die Elemente an pos1 und pos2 mit farbiger Anzeige und Verzögerung
void tausche(int arr[], int pos1, int pos2) {
    ++vertau;

    // zeichne die zu vertauschenden Balken färbig
    balken(arr, pos1, farbe_tausch);
    balken(arr, pos2, farbe_tausch);
    sdlMilliSleep(TAUSCH_MS);

    // zeichne den längeren alten Balken schwarz,
    // weil sonst würde nach dem Tausch beim Überzeichnen mit dem kürzeren Balken
    // oben ein Rest sichtbar bleiben!
    if (arr[pos1] > arr[pos2]) {
        balken(arr, pos1, farbe_schwarz);
    } else {
        balken(arr, pos2, farbe_schwarz);
    }

    // tausche
    int tmp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = tmp;

    // zeichne die vertauschten Balken normal
    balken(arr, pos1, farbe_normal);
    balken(arr, pos2, farbe_normal);
}

// Befülle das Array zufällig mit den Zahlen 1 bis anzahl
// und zeige den Anfangszustand an
void fuelle(int arr[], int anzahl) {
    for (int i = 0; i < anzahl; i++) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 3000; i++) {
        int x = rand() % anzahl;
        int y = rand() % anzahl;
        int tmp = arr[x];
        arr[x] = arr[y];
        arr[y] = tmp;
    }
    for (int i = 0; i < anzahl; i++) {
        balken(arr, i, farbe_normal);
    }
}

void bubble(int arr[], int anzahl) {
    for (int i = 0; i < anzahl; i++) {
        bool done = true;
        for (int j = 1; j < anzahl - i; j++) {
            if (kleiner(arr, j, j - 1)) {
                tausche(arr, j, j - 1);
                done = false;
            }
        }
        if (done) break;
    }
}

void selection(int arr[], int anzahl) {
    for (int i = 0; i < anzahl; i++) {
        int min = i;
        for (int j = i + 1; j < anzahl; j++) {
            if (kleiner(arr, j, min)) {
                min = j;
            }
        }
        tausche(arr, i, min);
    }
}

void insertion(int arr[], int anzahl) {
    for (int i = 1; i < anzahl; i++) {
        for (int j = i; j > 0; j--) {
            if (!kleiner(arr, j, j - 1)) {
                break;
            }
            tausche(arr, j, j - 1);
        }
    }
}

void shell(int arr[], int anzahl) {
    int steps[] = {301, 132, 57, 23, 10, 4, 1};
    int step_count = 7;
    for (int i = 0; i < step_count; i++) {
        for (int j = steps[i]; j < anzahl; j++) {
            for (int k = j; k >= steps[i]; k -= steps[i]) {
                if (!kleiner(arr, k, k - steps[i])) {
                    break;
                }
                tausche(arr, k, k - steps[i]);
            }
        }
    }
}

int partition(int arr[], int min, int max) {
    int comparator = max - 1;
    max--;
    while (true) {
        for (int i = min; i < max; i++) {
            if (kleiner(arr, comparator, i)) {
                min = i;
                break;
            }
        }
        for (int i = max; i > min; i--) {
            if (kleiner(arr, i, comparator)) {
                max = i;
                break;
            }
        }
        if (min < max) {
            tausche(arr, min, max);
        } else {
            break;
        }
    }
    return max;
}

void quick(int arr[], int min, int max) {
    if (max <= min) return;

    int middle = partition(arr, min, max);
    quick(arr, min, middle);
    quick(arr, middle, max);
}

// sortiere das Array
// unter Verwendung von "kleiner" und "tausche"
void sort(int arr[], int anzahl, char mode) {
    switch (mode) {
        case 'b':
            bubble(arr, anzahl);
            break;
        case 's':
            selection(arr, anzahl);
            break;
        case 'i':
            insertion(arr, anzahl);
            break;
        case 'h':
            shell(arr, anzahl);
            break;
        case 'q':
            quick(arr, 0, anzahl);
            break;
        default:
            break;
    }
}

int main(int argc,
    const char * argv[]) {
    if (argc != 3) {
        printf("Aufruf: %s anzahl verfahren\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int anzahl = atoi(argv[1]);
    char mode = argv[2][0];
    if ((anzahl <= 0) || (anzahl > SDL_X_SIZE / 2) || (anzahl > SDL_Y_SIZE)) {
        printf("%s: Die Anzahl muss größer 0 sein "
            "und in das Grafikfenster passen\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // Geometrie aus der Anzahl berechnen
    breite = SDL_X_SIZE / anzahl;
    hoehe = SDL_Y_SIZE / anzahl;
    xstart = (SDL_X_SIZE % anzahl) / 2;

    int array[anzahl];

    srand(time(NULL));

    sdlInit();
    sdlSetBlack();

    fuelle(array, anzahl);

    sdlMilliSleep(START_MS);

    sort(array, anzahl, mode);

    printf("%d Vergleiche\n%d Vertauschungen\n", vergl, vertau);

    sdlMilliSleep(ENDE_MS);
    sdlExit();

    exit(EXIT_SUCCESS);
}