// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        printf("Hallo, ich bin %s, wer bist du?\n", argv[0]);
    } else if (argc > 11) {
        printf("Hallo an alle!\n");
    } else {
        int i;
        for (i = argc - 1; i > 1; --i) {
            printf("Hallo, %s, %d. Platz!\n", argv[i], i);
        }
        printf("Hallo, %s, du bist Erster!\n", argv[1]);
        printf("Ihr seid %d Leute\n", argc - 1);
    }
    return 0;
}