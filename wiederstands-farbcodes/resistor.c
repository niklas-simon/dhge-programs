#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CODE_LENGTH 3

void get_out() {
    printf("usage: resistor.exe color1 color2 color3\nColors must be lowercase and one of black, brown, red, orange, yellow, green, blue, violet, grey, white.");
    exit(0);
}

const char *codes[] = {
    "black",
    "brown",
    "red",
    "orange",
    "yellow",
    "green",
    "blue",
    "violet",
    "grey",
    "white"
};
const int codes_count = 10;

int get_value(char *code) {
    int result = -1;
    for (int i = 0; i < codes_count; i++) {
        if (!strcmp(code, codes[i])) {
            result = i;
            break;
        }
    }
    if (result == -1) get_out();
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != CODE_LENGTH + 1) {
        get_out();
    }
    int sum = 0;
    for (int i = 0; i < CODE_LENGTH - 1; i++) {
        sum *= 10;
        sum += get_value(argv[i + 1]);
    }
    int multiplier = get_value(argv[CODE_LENGTH]);
    char factor = '\0';
    if (multiplier >= 9) {
        factor = 'G';
        multiplier -= 9;
    } else if (multiplier >= 6) {
        factor = 'M';
        multiplier -= 6;
    } else if (multiplier >= 3) {
        factor = 'k';
        multiplier -= 3;
    }
    sum *= pow(10, multiplier);
    if (factor) {
        printf("%i %cOhm", sum, factor);
    } else {
        printf("%i Ohm", sum);
    }
}