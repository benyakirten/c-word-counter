#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"
#include "read_file.h"

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        WordList *word_list = read_file(argv[i]);
        if (word_list == NULL)
        {
            fprintf(stderr, "Failed to read file: %s\n", argv[i]);
            return 1; // Exit with error
        }

        printf("Read %zu words from file %s\n", word_list->count, argv[i]);
        Hashmap *map = hashmap_from_words(word_list->words, word_list->count);
        printf("Created hashmap from words.\n");

        if (map == NULL)
        {
            fprintf(stderr, "Failed to create hashmap from words.\n");
            return 1; // Exit with error
        }

        printf("Word count for file %s:\n", argv[i]);
        printf("Total words: %zu\n", word_list->count);
        hashmap_print(map);

        free(word_list);
        hashmap_free(map);
    }
}
