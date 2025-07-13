#include "array_list.h"
#include "read_file.h"

#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE 1024

typedef struct
{
    ArrayList items[HASHMAP_SIZE];
} Hashmap;

Hashmap *hashmap_from_words(char words[MAX_WORD_COUNT][MAX_WORD_LENGTH], size_t word_count);
void hashmap_free(Hashmap *map);
size_t *hashmap_get(Hashmap *map, char *word);
bool hashmap_insert(Hashmap *map, char word[ARRAY_LIST_WORD_MAX_LENGTH]);
bool hashmap_remove(Hashmap *map, char *word);
void hashmap_print(Hashmap *map);
void hashmap_print_sorted(Hashmap *map);

#endif
