#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR "usage: palindromes.exe limit\nlimit must be an integer greather than 0"

void get_out() {
    printf(ERROR);
    exit(0);
}

bool is_palindrome(int number) {
    int copy = number;
    int reverse = 0;
    while (copy) {
        reverse *= 10;
        reverse += copy % 10;
        copy /= 10;
    }
    return reverse == number;
}

int main(int argc, char* argv[]) {
    if (argc != 2) get_out();
    int limit = atoi(argv[1]);
    if (limit <= 0) get_out();

    for (int i = 0; i < limit; i++) {
        if (is_palindrome(i)) printf("%i\n", i);
    }
    return 0;
}