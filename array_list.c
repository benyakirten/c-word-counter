#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "array_list.h"

void array_list_free(ArrayList *list);
bool array_list_grow(ArrayList *list, size_t *new_capacity);
bool array_list_remove_index(ArrayList *list, size_t index);

ArrayList *array_list_new(size_t *initial_capacity)
{
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL)
    {
        return NULL; // Memory allocation failed
    }
    list->size = 0;

    size_t capacity;
    if (initial_capacity == NULL || *initial_capacity < 1)
    {
        capacity = ARRAY_LIST_INITIAL_CAPACITY;
    }
    else
    {
        capacity = *initial_capacity;
    }

    list->capacity = capacity;
    list->data = malloc(capacity * sizeof(ArrayListItem));

    if (list->data == NULL)
    {
        free(list);
        return NULL; // Memory allocation failed
    }
    return list;
}

void array_list_free(ArrayList *list)
{
    if (list != NULL)
    {
        free(list->data);
        free(list);
    }
}

bool array_list_push(ArrayList *list, char word[ARRAY_LIST_WORD_MAX_LENGTH])
{
    if (list->size >= list->capacity)
    {
        bool result = array_list_grow(list, NULL);
        if (!result)
        {
            return false; // Memory allocation failed
        }
    }

    ArrayListItem item;
    strncpy(item.word, word, ARRAY_LIST_WORD_MAX_LENGTH);
    item.count = 1;

    list->data[list->size] = item;
    list->size++;

    return true;
}

void array_list_shrink(ArrayList *list)
{
    if (list->size >= list->capacity)
    {
        return; // No need to shrink if size is equal or greater than capacity
    }

    ArrayListItem *new_list = realloc(list->data, list->size * sizeof(ArrayListItem));
    if (new_list == NULL)
    {
        return; // Memory allocation failed
    }

    list->data = new_list;
    list->capacity = list->size;
}

ArrayListItem *array_list_pop(ArrayList *list)
{
    if (list->size == 0)
    {
        return NULL;
    }

    size_t last_index = list->size - 1;

    ArrayListItem *value = malloc(sizeof(ArrayListItem));
    if (value == NULL)
    {
        return NULL; // Memory allocation failed
    }

    memcpy(value, &list->data[last_index], sizeof(ArrayListItem));
    list->size--;

    return value;
}

ArrayListItem *array_list_get(ArrayList *list, size_t index)
{
    if (index >= list->size || index < 0)
    {
        return NULL;
    }

    return &list->data[index];
}

bool array_list_remove(ArrayList *list, char word[ARRAY_LIST_WORD_MAX_LENGTH])
{
    for (size_t i = 0; i < list->size; i++)
    {
        ArrayListItem value = list->data[i];
        if (strcmp(value.word, word) == 0)
        {
            array_list_remove_index(list, i);
            return true;
        }
    }
    return false;
}

bool array_list_remove_index(ArrayList *list, size_t index)
{
    if (index >= list->size || index < 0)
    {
        return false;
    }

    for (size_t i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->size--;

    return true;
}

bool array_list_grow(ArrayList *list, size_t *new_capacity)
{
    size_t capacity;
    if (new_capacity == NULL || *new_capacity < list->capacity * ARRAY_LIST_CAPACITY_GROWTH_FACTOR_MIN)
    {
        capacity = list->capacity * ARRAY_LIST_CAPACITY_GROWTH_FACTOR;
    }
    else
    {
        capacity = *new_capacity;
    }

    if (capacity <= list->capacity * ARRAY_LIST_CAPACITY_MAX_RATIO)
    {
        return false; // No need to grow if the new capacity is less than the max ratio
    }

    ArrayListItem *data = realloc(list->data, capacity * sizeof(ArrayListItem));
    if (data == NULL)
    {
        return false; // Memory allocation failed
    }
    else
    {
        list->data = data;
    }

    list->capacity = capacity;
    return true;
}

ArrayListItem *array_list_find(ArrayList *list, char word[ARRAY_LIST_WORD_MAX_LENGTH])
{
    for (size_t i = 0; i < list->size; i++)
    {
        if (strcmp(list->data[i].word, word) == 0)
        {
            return &list->data[i];
        }
    }
    return NULL;
}
