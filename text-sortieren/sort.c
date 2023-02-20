#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ROWS 16
#define COLS 4096

typedef struct {
    int number;
    const char *text;
} Line;

int compare(const void *s1, const void *s2) {
    return strcmp(((Line *) s1)->text, ((Line *) s2)->text);
}

Line *reallocate(char *name, Line *lines, int length) {
    lines = (Line *) realloc(lines, length * sizeof(Line));
    if (!lines) {
        printf("%s: Error while allocating memory: %s", name, strerror(errno));
        exit(errno);
    }
    return lines;
}

FILE *tryopen(char *name, char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        fprintf(stderr, "%s: Error while reading file %s: %s", name, filename, strerror(errno));
        exit(errno);
    }
    return file;
}

int main(int argc, char **argv) {
    if (argc > 3) {
        fprintf(stderr, "%s: usage: sort.out [input file] [output file]", argv[0]);
        exit(1);
    }
    FILE *in = stdin;
    if (argc > 1) {
        in = tryopen(argv[0], argv[1], "r");
    }
    FILE *out = stdout;
    if (argc == 3) {
        out = tryopen(argv[0], argv[2], "w");
    }

    int maxlen = ROWS;
    Line *lines;
    lines = reallocate(argv[0], lines, maxlen);
    if (!lines) {
        fprintf(stderr, "%s: Error while allocating memory: %s", argv[0], strerror(errno));
        exit(errno);
    }

    int i = 0;
    char line[COLS];
    for (; fgets(line, COLS, in); i++) {
        if (i >= maxlen) {
            maxlen *= 2;
            lines = reallocate(argv[0], lines, maxlen);
        }
        if (!strchr(line, '\n')) {
            fprintf(stderr, "%s: Error while reading line %i: Line too long.", argv[0], i);
            exit(1);
        }
        lines[i].text = strdup(line);
        if (!lines[i].text) {
            fprintf(stderr, "%s: Error while allocating memory: %s", argv[0], strerror(errno));
            exit(errno);
        }
        lines[i].number = i + 1;
    }
    int length = i;

    qsort(lines, length, sizeof(Line), compare);

    int maxdigits = 0;
    int lencpy = length;
    while (lencpy) {
        lencpy /= 10;
        maxdigits++;
    }

    for (int i = 0; i < length; i++) {
        fprintf(out, "%*d: %s", maxdigits, lines[i].number, lines[i].text);
    }
}