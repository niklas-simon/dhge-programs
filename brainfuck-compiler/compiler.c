#define ERROR "Benutzung: compiler.exe datei.bf"
#include <stdio.h>

int get_count(char* filename) {
    int count = 0;
    FILE *input = fopen(filename, "r");

    char c = fgetc(input);
    while (c != EOF) {
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
                count++;
                break;
            case '[':
            case ']':
                count += 2;
                break;
            default:
                break;
        }
        c = fgetc(input);
    }

    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf(ERROR);
        return 0;
    }

    int conversion[256];
    conversion['>'] = 1;
    conversion['<'] = 2;
    conversion['+'] = 3;
    conversion['-'] = 4;
    conversion['.'] = 5;
    conversion[','] = 6;
    conversion['['] = 7;
    conversion[']'] = 8;

    int int_to_hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    int count = get_count(argv[1]) + 2;
    unsigned char buffer[count];
    buffer[0] = 255;

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen("out.txt", "w");

    char c = fgetc(input);
    int pointer = 1;
    while (c != EOF) {
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
                buffer[pointer] = conversion[c];
                pointer++;
                break;
            case '[':
            case ']':
                buffer[pointer] = conversion[c];
                pointer++;
                // pointer at addr of ]
                if (c == ']') {
                    int last_open = -1;
                    for (int i = pointer - 1; i >= 0; i--) {
                        if (buffer[i] == conversion['[']) {
                            last_open = i + 1;
                            // last_open at addr of [
                            break;
                        }
                    }
                    if (last_open == -1) {
                        return 0;
                    }
                    // set addr of ] to after addr of [
                    buffer[pointer] = last_open + 1;
                    pointer++;
                    // set addr of [ to after addr of ]
                    buffer[last_open] = pointer;
                } else {
                    buffer[pointer] = 0;
                    pointer++;
                }
                break;
            default:
                break;
        }
        c = fgetc(input);
    }
    buffer[pointer] = 0;

    fputs("v2.0 raw\n", output);
    for (int i = 0; i < count; i++) {
        fputc(int_to_hex[buffer[i] / 16], output);
        fputc(int_to_hex[buffer[i] % 16], output);
        if (i + 1 < count) fputc(' ', output);
    }

    fclose(output);
    fclose(input);

    return 0;
}