#include "array_list.h"

#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE 1024

typedef struct
{
    ArrayList *items[HASHMAP_SIZE];
} Hashmap;

Hashmap *hashmap_new();
Hashmap *hashmap_from_file(char *path);
void hashmap_free(Hashmap *map);
size_t *hashmap_get(Hashmap *map, char *word);
bool hashmap_insert(Hashmap *map, char word[ARRAY_LIST_WORD_MAX_LENGTH]);
bool hashmap_remove(Hashmap *map, char *word);
void hashmap_print(Hashmap *map);

#endif
