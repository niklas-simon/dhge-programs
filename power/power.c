// Potenz zweier ganzer Zahlen (a hoch n)
// Programm-Skelett zur Angabe
//
// Aufruf: power a n
//
// Klaus Kusche, 2010

#include <stdio.h>
// Was steht in der Angabe zu atoi, was an dieser Stelle zu beachten ist?
#include <stdlib.h>

#define ERROR "Nutzung: power.exe zahl1 zahl2\nBeide Zahlen müssen Ganzzahlen größer gleich 0 sein, es dürfen jedoch nicht beide Zahlen 0 sein!"

int main(int argc, const char *argv[])
{
    // hat der Aufrufer überhaupt zwei Zahlen angegeben?
    // (damit argv[1] und argv[2] nicht "ins Leere greift")

        // Wenn nein: Fehlermeldung ausgeben, mit Fehlercode aufhören

    // argv[1] und argv[2] in Zahlen verwandeln
    // und in zwei dafür angelegten Variablen speichern

    // jetzt sollten wir noch prüfen,
    // ob wir es mit mathematisch sinnvollen Eingaben zu tun haben:
    // Bei ganzzahliger Rechnung können wir nur Exponenten >= 0 berechnen
    // Sonst: Fehlermeldung, aufhören!
    // (und "0 hoch 0" sollte auch ausgeschlossen werden, aber das sparen wir uns)

    // Wir brauchen eine Variable für das Ergebnis
    // im Ergebnis speichern wir als Anfangswert einmal 1,
    // damit wir weiter unten etwas dazumultiplizieren können

    // und dann kommt eine Schleife,
    // die von 1 bis zur zweiten Eingabe (einschließlich) zählt

        // in der Schleife multiplizieren wir jedesmal
        // die erste Eingabe zum Ergebnis dazu
        // und speichern das wieder im Ergebnis

    // nach der Schleife kommt noch die Ausgabe ...

    // ... und das Programm-Ende

    if (argc != 3) {
        printf(ERROR);
        return 0;
    }
    int n = atoi(argv[1]);
    int e = atoi(argv[2]);
    if (n < 0 || e < 0 || (n == 0 && e == 0)) {
        printf(ERROR);
        return 0;
    }
    int result = 1;
    for (int i = 0; i < e; i++) result *= n;
    printf("%d", result);
    return 0; 
}