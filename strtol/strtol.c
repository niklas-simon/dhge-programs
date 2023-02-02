#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int strtoi(const char *str, const char **end) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    for (; *str, isdigit(*str); str++) {
        result *= 10;
        result += *str - '0';
    }
    if (*str && end) *end = str;
    return sign * result;
}

int main(int argc, const char **argv) {
    for (int i = 1; i < argc; i++) {
        const char *end = NULL;
        int result = strtoi(argv[i], &end);
        if (end == NULL) {
            printf("%i\n", result);
        } else {
            printf("stopped at '%c' when converting \"%s\", skipping it.\n", *end, argv[i]);
        }
    }
}