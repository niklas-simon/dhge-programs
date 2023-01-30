#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 100

char *get_next_word(char *pos) {
    pos++;
    for (; isalpha(*pos); pos++) {}
    return pos;
}

int main() {
    for (;;) {
        char line[LENGTH];
        printf("new sentence please (or Ctrl+Z, then ENTER to quit):\n");
        if (!fgets(line, sizeof(line), stdin)) return 0;

        char *pos = line;
        while (*pos != '\0') {
            char *newpos = pos;
            newpos = get_next_word(newpos);
            
            char word[newpos - pos + 1];
            for (int i = 0; i < newpos - pos; i++) {
                word[i] = pos[i];
            }
            word[newpos - pos] = '\0';

            pos = newpos + 1;
            printf("%s\n", word);
        }
    }
}