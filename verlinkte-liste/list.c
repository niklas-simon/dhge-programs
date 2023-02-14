#include <stdlib.h>
#include <stdio.h>

typedef struct Item {
    struct Item *last;
    int value;
    int count;
    struct Item *next;
} Item;

void print(Item *list) {
    for (; list; list = list->next) {
        printf("%i:%i", list->value, list->count);
        if (list->next) {
            printf(", ");
        }
    }
    printf("\n");
}

Item *add(Item *list, int value) {
    Item *ptr = list;
    Item *item = (Item*) malloc(sizeof(Item));
    item->value = value;
    item->count = 1;

    if (!ptr) {
        item->last = NULL;
        item->next = NULL;
    } else {
        for (; ptr && ptr->value < value; ptr = ptr->next) {}
        // ptr is now at first element that is greather than or equal to item
        if (!ptr) {
            // item is biggest so far
            item->next = NULL;
            // reset pointer to last element
            ptr = list;
            for (; ptr->next; ptr = ptr->next) {}
            item->last = ptr;
            ptr->next = item;
        } else if (ptr->value != value) {
            // only add unique values
            item->next = ptr;
            item->last = ptr->last;
            ptr->last = item;
        } else {
            ptr->count++;
        }
    }

    ptr = ptr ? ptr : item;
    // reset pointer to first
    for (; ptr->last; ptr = ptr->last) {}

    print(ptr);
    return ptr;
}

int main(int argc, char **argv) {
    Item *list = NULL;
    for (int i = 1; i < argc; i++) {
        list = add(list, atoi(argv[i]));
    }
}