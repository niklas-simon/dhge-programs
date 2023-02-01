#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int numerator;
    int denominator;
} fraction;

void get_out() {
    printf("usage: fraction fraction1 operand fraction2");
    exit(0);
}

fraction optimize(fraction f) {
    for (int i = f.numerator; i > 1; i--) {
        while (f.numerator % i == 0 && f.denominator % i == 0) {
            f.numerator /= i;
            f.denominator /= i;
        }
    }
    return f;
}

fraction add(fraction f1, fraction f2) {
    fraction sum = {
        f1.numerator * f2.denominator + f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    };
    return optimize(sum);
}

fraction substract(fraction f1, fraction f2) {
    fraction res = {
        f1.numerator * f2.denominator - f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    };
    return optimize(res);
}

fraction multiply(fraction f1, fraction f2) {
    fraction res = {
        f1.numerator * f2.numerator,
        f1.denominator * f2.denominator
    };
    return optimize(res);
}

fraction divide(fraction f1, fraction f2) {
    int tmp = f2.numerator;
    f2.numerator = f2.denominator;
    f2.denominator = tmp;

    return multiply(f1, f2);
}

fraction fromString(char *string) {
    char *end = string + strlen(string);
    char *seperator = strchr(string, '/');
    fraction f = {1, 1};
    if (seperator) {
        f.numerator = strtol(string, &seperator, 10);
        seperator++;
        f.denominator = strtol(seperator, &end, 10);
    } else {
        f.numerator = strtol(string, &end, 10);
    }
    return f;
}

fraction calculate(fraction f1, fraction f2, char operand) {
    switch (operand)
    {
        case '+':
            return add(f1, f2);
        case '-':
            return substract(f1, f2);
        case 'x':
            return multiply(f1, f2);
        case ':':
            return divide(f1, f2);
        default:
            get_out();
            fraction f = {1, 1};
            return f;
    }
}

int main(int argc, char **argv) {
    if (argc != 4) get_out();
    fraction f1 = fromString(argv[1]);
    fraction f2 = fromString(argv[3]);
    if (f1.denominator == 0 || f2.denominator == 0) get_out();
    char operand = argv[2][0];
    fraction f = calculate(f1, f2, operand);
    printf("%i/%i", f.numerator, f.denominator);
}