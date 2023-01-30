#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void get_out() {
    printf("usage: permutation.exe length");
    exit(0);
}

void swap(int *pos1, int *pos2) {
    int tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

void reverse(int *pos1, int *pos2) {
    for (; pos1 < pos2; pos1++, pos2--) {
        swap(pos1, pos2);
    }
}

int *find_smaller(int *arr, int *end) {
    end--;
    for (; end >= arr; end--) {
        if (*end < end[1]) return end;
    }
    return NULL;
}

int *find_larger(int *arr, int *end, int *comparator) {
    for (; end >= arr; end--) {
        if (*end > *comparator) return end;
    }
    return NULL;
}

bool perm(int *arr, int *end) {
    int *left = find_smaller(arr, end);
    if (!left) return false;
    int *right = find_larger(arr, end, left);
    if (!right) return false;
    swap(left, right);
    reverse(++left, end);
    return true;
}

void fill(int *arr, int *end) {
    for (int i = 1; arr <= end; arr++, i++) {
        *arr = i;
    }
}

void print(int *arr, int *end, int *count) {
    printf("%7i:", *count);
    for (; arr <= end; arr++) {
        printf(" %2i", *arr);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Ah yes, Pointer!
    if (argc != 2) get_out();
    int length = atoi(argv[1]);
    if (length < 1 || length > 30) get_out();
    int arr[length];
    int *end = &arr[length];
    fill(arr, end);
    int count = 1;
    do {
        print(arr, end, &count);
        count++;
    } while (perm(arr, end));
}