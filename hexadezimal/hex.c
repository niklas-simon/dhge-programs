#include <stdlib.h>
#include <stdio.h>

#define ERROR "Nutzung: hex.exe zahl1 [zahl2 ... zahln] \nZahlen muessen Hexadezimalganzzahlen groeßer gleich 0 sein!\n"
#define INVALID_DIGIT "'%c' ist keine Hexadezimalziffer. Zahl mit dieser Ziffer wird uebersprungen.\n"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf(ERROR);
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        int decimal = 0;
        for (int j = 0; argv[i][j] != '\0'; j++) {
            decimal = decimal * 16;
            switch (argv[i][j]) {
                case '0'...'9':
                    decimal += argv[i][j] - '0';
                    break;
                case 'a'...'f':
                    decimal += argv[i][j] - 'a' + 10;
                    break;
                case 'A'...'F':
                    decimal += argv[i][j] - 'A' + 10;
                    break;
                default:
                    printf(INVALID_DIGIT, argv[i][j]);
                    goto next_number;
            }
        }
        printf("%s in Hexadezimal ist %d\n", argv[i], decimal);
        next_number: ;
    }
    return 0;
}