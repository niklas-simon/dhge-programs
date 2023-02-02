#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void get_out() {
    printf("usage: wildcard.c string pattern\n");
    exit(0);
}

bool matches(const char *string, const char *pattern) {
    for (;; string++, pattern++) {
        printf("comparing %c to %c\n", *string, *pattern);
        if (!*pattern) return !*string;
        if (*pattern == '*') {
            const char *pos = string;
            for (; pos; pos++) {
                if (matches(pos, pattern + 1)) return true;
            }
            return false;
        }
        if (!*string && *pattern) return false;
        if (*pattern == '?') continue;
        if (*string != *pattern) return false;
    }
}

int main(int argc, const char **argv) {
    if (argc != 3) get_out();
    printf("%i\n", matches(argv[1], argv[2]));
}