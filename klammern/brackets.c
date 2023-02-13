#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#define OK 0
#define INCORRECT 1
#define MULTIPLE 2
#define MISSING 3

typedef struct {
    int code;
    int row;
    int col;
} Result;

void get_out() {
    printf("usage: brackets.out file1 [file2 file3 ... fileN]");
    exit(0);
}

void printerr(int code, int row, int col) {
    switch (code) {
        case OK:
            printf("File is correct");
            break;
        case INCORRECT:
            printf("Incorrect closing bracket at char %i in line %i", col, row);
            break;
        case MULTIPLE:
            printf("Too many closing brackets at char %i in line %i", col, row);
            break;
        case MISSING:
            printf("Not all brackets are being closed");
            break;
    }
}

int isOpening(char c) {
    if (c == '(' || c == '[' || c == '{') {
        return c;
    }
    return 0;
}

int isClosing(char c) {
    if (c == ')' || c == ']' || c == '}') {
        return c;
    }
    return 0;
}

int matches(char opening, char closing) {
    return (opening == '(' && closing == ')')
        || (opening == '[' && closing == ']')
        || (opening == '{' && closing == '}');
}

Result findClosing(FILE *file, int row, int col, int opening);

Result findOpening(FILE *file, int row, int col) {
    int opening;
    do {
        opening = fgetc(file);
        col++;
        if (opening == '\n') {
            row++;
            col = 0;
        }
        if (isClosing(opening)) {
            return (Result){MULTIPLE, row, col};
        }
    } while (!isOpening(opening) && opening != EOF);
    if (opening == EOF) return (Result){OK, row, col};

    return findClosing(file, row, col, opening);
}

Result findClosing(FILE *file, int row, int col, int opening) {
    int closing;
    do {
        closing = fgetc(file);
        col++;
        if (closing == '\n') {
            row++;
            col = 0;
        }
        if (isOpening(closing)) {
            ungetc(closing, file);
            Result res = findOpening(file, row, --col);
            row = res.row;
            col = res.col;
            if (res.code != OK) return res;
        }
    } while (!isClosing(closing) && closing != EOF);
    if (opening == EOF && closing == EOF) return (Result){OK, row, col};
    if (closing == EOF) return (Result){MISSING, row, col};

    if (matches(opening, closing)) {    
        if (opening == EOF) {
            return findOpening(file, row, col);
        }
        return (Result){OK, row, col};
    } else {
        if (opening == EOF) {
            return (Result){MULTIPLE, row, col};
        }
        return (Result){INCORRECT, row, col};
    }
}

void check(FILE *file) {
    Result res = findClosing(file, 1, 0, EOF);
    printerr(res.code, res.row, res.col);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        check(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "%s: Error while opening %s: Could not open file.", argv[0], argv[i]);
                exit(errno);
            }
            
            check(file);

            fclose(file);
        }
    }
    return 0;
}