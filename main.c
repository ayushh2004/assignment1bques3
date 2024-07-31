#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

void to_lowercase(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

int is_word_char(char c) {
    return isalpha(c) || c == '\'';
}

void add_word(char words[][MAX_WORD_LEN], int count[], int *word_count, char *word) {
    for (int i = 0; i < *word_count; ++i) {
        if (strcmp(words[i], word) == 0) {
            count[i]++;
            return;
        }
    }
    strcpy(words[*word_count], word);
    count[*word_count] = 1;
    (*word_count)++;
}

int main() {
    char paragraph[5000];
    char words[MAX_WORDS][MAX_WORD_LEN] = {0};
    int count[MAX_WORDS] = {0};
    int word_count = 0;

    printf("Enter a paragraph: ");
    fgets(paragraph, sizeof(paragraph), stdin);

    char *word = strtok(paragraph, " ,.-\n");
    while (word != NULL) {
        char clean_word[MAX_WORD_LEN] = {0};
        int j = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            if (is_word_char(word[i])) {
                clean_word[j++] = tolower(word[i]);
            }
        }
        clean_word[j] = '\0';
        if (j > 0) {
            add_word(words, count, &word_count, clean_word);
        }
        word = strtok(NULL, " ,.-\n");
    }

    printf("\nWord frequencies:\n");
    for (int i = 0; i < word_count; ++i) {
        printf("%s: %d\n", words[i], count[i]);
    }

    return 0;
}
