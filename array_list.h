#include <stddef.h>
#include <stdbool.h>

#include "words.h"

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define ARRAY_LIST_INITIAL_CAPACITY 10
#define ARRAY_LIST_CAPACITY_GROWTH_FACTOR 1.5
#define ARRAY_LIST_CAPACITY_GROWTH_FACTOR_MIN 1.2
#define ARRAY_LIST_CAPACITY_MAX_RATIO 0.75

typedef struct
{
    char word[WORD_MAX_LENGTH];
    size_t count;
} ArrayListItem;

typedef struct
{
    size_t size;
    size_t capacity;
    ArrayListItem *data;
} ArrayList;

ArrayList *array_list_new(size_t *initial_capacity);
void array_list_free(ArrayList *list);
bool array_list_remove(ArrayList *list, char word[WORD_MAX_LENGTH]);
bool array_list_push(ArrayList *list, char word[WORD_MAX_LENGTH]);
void array_list_shrink(ArrayList *list);
ArrayListItem *array_list_find(ArrayList *list, char word[WORD_MAX_LENGTH]);

#endif
