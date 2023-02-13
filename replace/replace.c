#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define LINE_LENGTH 4096

void get_out() {
    fprintf(stderr, "usage: replace.out search replace [input file] [output file]");
    exit(0);
}

void replace(FILE *file, FILE *out, char *search, char *replace) {
    char line[LINE_LENGTH];
    char *ptr = line;
    char *found = NULL;
    int search_len = strlen(search);
    while (found || fgets(ptr, LINE_LENGTH, file)) {
        found = strstr(ptr, search);
        if (found) {
            *found = '\0';
            fprintf(out, "%s%s", ptr, replace);
            ptr = found + search_len;
        } else {
            fprintf(out, "%s", ptr);
            ptr = line;
        }
    }
}

int main(int argc, char **argv) {
    FILE *file;
    FILE *out;
    if (argc < 3) {
        get_out();
    }
    if (argc > 3) {
        file = fopen(argv[3], "r");
    } else {
        file = stdin;
    }
    if (argc == 5) {
        out = fopen(argv[4], "w");
    } else {
        out = stdout;
    }
    if (!file || !out) {
        fprintf(stderr, "%s: Error while opening files: %s\n", argv[0], strerror(errno));
        exit(errno);
    }
    replace(file, out, argv[1], argv[2]);
    fclose(file);
    fclose(out);
}