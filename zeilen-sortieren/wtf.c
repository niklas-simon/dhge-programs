#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define LENTH 4096

typedef struct Item {
    char *filename;
    int line;
    char *text;
    struct Item *next;
} Item;

typedef struct List {
    Item *head;
    Item *tail;
} List;

void add(List *lists, char *filename, int line, char *text) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (!item) {
        fprintf(stderr, "Error while allocating memory: %s", strerror(errno));
        exit(errno);
    }

    char *text_copy = strdup(text);
    item->text = text_copy;

    item->filename = filename;
    item->line = line;
    item->next = NULL;

    int length = strlen(text);
    if (length >= LENTH) {
        fprintf(stderr, "Error while adding line %i from %s to list: Line is too long.", line, filename);
        exit(1);
    }
    if (!lists[length].head) {
        lists[length].head = item;
        lists[length].tail = item;
    } else {
        lists[length].tail->next = item;
        lists[length].tail = item;
    }
}

void readFile(List *lists, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error while opening %s: %s", filename, strerror(errno));
        exit(errno);
    }

    int line = 1;
    char text[LENTH];
    while (fgets(text, LENTH, file)) {
        if (!strchr(text, '\n') && strlen(text) >= LENTH){
            fprintf(stderr, "Error while copying line %i from %s: Line is too long.", line, filename);
            exit(1);
        }
        add(lists, filename, line, text);
        line++;
    }

    fclose(file);
}

void print(List *lists) {
    for (int i = 0; i < LENTH; i++) {
        for (Item *ptr = lists[i].head; ptr; ptr = ptr->next) {
            printf("%s line %3i: %s", ptr->filename, ptr->line, ptr->text);
        }
    }
}

int main(int argc, char **argv) {
    List lists[LENTH];
    for (int i = 0; i < LENTH; i++) {
        lists[i] = (List){NULL, NULL};
    }

    for (int i = 1; i < argc; i++) {
        readFile(lists, argv[i]);
    }

    print(lists);

    return 0;
}