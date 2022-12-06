#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc == 2) printf("Hello %s\n", argv[1]);
    else printf("Hello Unknown Human!\n");
    return 0;
}