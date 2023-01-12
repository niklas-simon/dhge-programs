#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ERROR "Usage: calculator.exe number1 operand1 number2 [operand2 number3]+ \nOperands must be one of + - x / ^!\n"

int main(int argc, const char *argv[]) {
    if (argc % 2 != 0 || argc < 4) {
        printf(ERROR);
        return 0;
    }
    double result = atof(argv[1]);
    for (int i = 3; i < argc; i += 2) {
        switch (argv[i - 1][0]) {
            case '+':
                result += atof(argv[i]);
                break;
            case '-':
                result -= atof(argv[i]);
                break;
            case 'x':
                result *= atof(argv[i]);
                break;
            case '/':
                result /= atof(argv[i]);
                break;
            case '^':
                result = pow(result, atof(argv[i]));
                break;
            default:
                printf(ERROR);
                return 0;
        }
    }
    printf("%f", result);
    return 0;
}