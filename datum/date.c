#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const char weekdays[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void get_out() {
    printf("usage: date year month day");
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 4) get_out();
    int year = atoi(argv[1]);
    int month = atoi(argv[2]);
    int day = atoi(argv[3]);
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 3000) 
        get_out();

    struct tm date = {0, 0, 0, day, month - 1, year - 1900, 0, 0, -1};
    time_t time = mktime(&date);
    struct tm newdate = *localtime(&time);
    printf("%i-%i-%i is day %i of the year and a %s\n", 
        newdate.tm_year + 1900,
        newdate.tm_mon + 1,
        newdate.tm_mday,
        newdate.tm_yday + 1,
        weekdays[newdate.tm_wday]
    );
}