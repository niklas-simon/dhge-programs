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
        printf("Hallo, ");
        for (int i = 1; i < argc; ++i) {
            printf(argv[i]);
            if (i == argc - 2) printf(" und ");
            else if (i < argc - 2) printf(", ");
        }
        printf("!\n");
        printf("Ihr seid %d Leute\n", argc - 1);
    }
    return 0;
}