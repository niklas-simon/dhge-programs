#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void get_out() {
    printf("usage: dir directory");
    exit(0);
}

static int cmpstringp(const void *p1, const void *p2) {
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int main(int argc, char **argv) {
    if (argc != 2) get_out();
    chdir(argv[1]);
    DIR *dir = opendir(".");
    if (!dir) get_out();
    char *dirs[256];
    struct dirent *entry = readdir(dir);
    int i = 0;
    for (; entry && i < 256; i++) {
        dirs[i] = strdup(entry->d_name);
        entry = readdir(dir);
    }
    qsort(dirs, i, sizeof(char *), cmpstringp);
    struct stat stats[i + 1];
    int max_size = 0;
    for (int j = 0; j < i; j++) {
        struct stat properties;
        if (stat(dirs[j], &properties)) {
            stats[j] = (struct stat){};
        } else {
            stats[j] = properties;
            if (properties.st_size > max_size) {
                max_size = properties.st_size;
            }
        }
    }
    int digits = 0;
    while (max_size > 0) {
        digits++;
        max_size /= 10;
    }
    for (int j = 0; j < i; j++) {
        char size[digits + 1];
        size[digits] = '\0';
        int st_size = stats[j].st_size;
        for (int k = digits - 1; k >= 0; k--) {
            if (st_size) {
                size[k] = '0' + st_size % 10;
                st_size /= 10;
            } else {
                size[k] = ' ';
            }
        }

        printf("%s %i %s\n", 
            size, 
            stats[j].st_mode,
            dirs[j]
        );
    }
}