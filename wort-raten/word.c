#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "words.h"

int get_words_length() {
    int i = 0;
    for (; words[i][0] != '\0'; i++) {}
    return i + 1;
}

void put_random_word(char *out, int length) {
    strcpy(out, words[rand() % length]);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int length = get_words_length();
    const char *word = words[rand() % length];
    int word_length = strlen(word);

    char shown_word[word_length + 1];
    for (int i = 0; i < word_length; i++) {
        shown_word[i] = '_';
    }
    shown_word[word_length] = '\0';

    int wrong_tries = 0;
    while (strchr(shown_word, '_')) {
        printf(shown_word);
        printf("\nInput character or whole word: ");
        char input[100];
        scanf("%s", input);
        if (input[0] == '\0') continue;
        if (input[1] == '\0') {
            // single character
            bool got_one = false;
            for (int i = 0; i < word_length; i++) {
                if (word[i] == input[0]) {
                    shown_word[i] = input[0];
                    got_one = true;
                }
            }
            if (!got_one) wrong_tries++;
            continue;
        }
        // whole word
        if (!strcmp(word, input)) {
            break;
        }
        printf("Wrong. Try again!\n");
    }
    printf("You got to the right word with %i wrong tries. The word was ", wrong_tries);
    printf(word);
    printf("\n");
}