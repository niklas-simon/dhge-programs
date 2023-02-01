#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void get_out() {
    printf("usage: dir directory");
    exit(0);
}

static int cmpstringp(const void *p1, const void *p2) {
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int main(int argc, char **argv) {
    if (argc != 2) get_out();
    DIR *dir = opendir(argv[1]);
    if (!dir) get_out();
    char *dirs[256];
    struct dirent *entry = readdir(dir);
    int i = 0;
    for (; entry; i++) {
        dirs[i] = strdup(entry->d_name);
        entry = readdir(dir);
    }
    qsort(dirs, i, sizeof(char *), cmpstringp);
    for (int j = 0; j < i; j++) {
        struct stat properties;
        int res = stat(dirs[j], &properties);
        if (stat(dirs[j], &properties)) {
            printf("%s\n", dirs[j]);
        } else {
            char *t = ctime(&properties.st_mtime);
            if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
            printf("%5ld %i %s %s\n", 
                properties.st_size, 
                properties.st_mode, 
                t, 
                dirs[j]
            );
        }
    }
}