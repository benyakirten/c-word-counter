#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashmap.h"
#include "read_file.h"
#include "array_list.h"

int hash(char *key)
{
    int hash = 0;
    while (*key)
    {
        hash = (hash << 0b101) - hash + (unsigned char)(*key++);
    }
    return hash % HASHMAP_SIZE;
}

Hashmap *hashmap_new()
{
    Hashmap *map = malloc(sizeof(Hashmap));
    if (map == NULL)
    {
        return NULL; // Memory allocation failed
    }

    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        ArrayList *array_list = array_list_new(NULL);
        if (array_list == NULL)
        {
            // Free previously allocated lists before returning
            for (size_t j = 0; j < i; j++)
            {
                if (map->items[j].data != NULL)
                {
                    free(map->items[j].data);
                }
            }
            free(map);
            return NULL; // Memory allocation failed
        }

        // Copy the ArrayList contents but keep the data pointer
        map->items[i] = *array_list;
        // Free only the ArrayList wrapper, not the data
        free(array_list);
    }

    return map;
}

Hashmap *hashmap_from_words(char word_list[MAX_WORD_COUNT][MAX_WORD_LENGTH], size_t word_count)
{
    Hashmap *map = hashmap_new();
    if (map == NULL)
    {
        return NULL; // Memory allocation failed
    }

    for (size_t i = 0; i < word_count; i++)
    {
        char *word = word_list[i];
        if (!hashmap_insert(map, word))
        {
            return map;
        }
    }

    return map;
}

void hashmap_free(Hashmap *map)
{
    if (map != NULL)
    {
        for (size_t i = 0; i < HASHMAP_SIZE; i++)
        {
            // Only free the data portion, not the ArrayList struct itself
            // since it's embedded in the hashmap struct
            if (map->items[i].data != NULL)
            {
                free(map->items[i].data);
            }
        }
        free(map);
    }
}

size_t *hashmap_get(Hashmap *map, char *word)
{
    int hash_value = hash(word);
    ArrayList *array_list = &map->items[hash_value];

    if (array_list == NULL)
    {
        return NULL; // No list found for this hash value
    }

    ArrayListItem *item = array_list_find(array_list, word);
    if (item == NULL)
    {
        return NULL; // Word not found in the list
    }

    return &item->count;
}

bool hashmap_insert(Hashmap *map, char word[ARRAY_LIST_WORD_MAX_LENGTH])
{
    int hash_value = hash(word);
    ArrayList *array_list = &map->items[hash_value];
    ArrayListItem *item = array_list_find(array_list, word);

    if (item != NULL)
    {
        item->count++;
    }
    else
    {
        array_list_push(array_list, word);
    }

    return true;
}

bool hashmap_remove(Hashmap *map, char *word)
{
    int hash_value = hash(word);
    ArrayList *array_list = &map->items[hash_value];

    if (array_list == NULL || array_list == NULL)
    {
        return false; // No list found for this hash value
    }

    return array_list_remove(array_list, word);
}

void hashmap_print(Hashmap *map)
{
    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        ArrayList array_list = map->items[i];

        for (size_t j = 0; j < array_list.size; j++)
        {
            ArrayListItem array_item = array_list.data[j];
            printf("Word: %s, Count: %zu\n", array_item.word, array_item.count);
        }
    }
}

int compare_items_desc(const void *a, const void *b)
{
    const ArrayListItem *item1 = (const ArrayListItem *)a;
    const ArrayListItem *item2 = (const ArrayListItem *)b;

    if (item1->count < item2->count)
        return 1;
    if (item1->count > item2->count)
        return -1;
    return 0;
}

void hashmap_print_sorted(Hashmap *map)
{
    // First, count total number of items
    size_t total_items = 0;
    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        total_items += map->items[i].size;
    }

    // Allocate space for all items
    ArrayListItem *all_items = malloc(total_items * sizeof(ArrayListItem));
    if (all_items == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for item collection\n");
        return;
    }

    // Copy all items into the flat array
    size_t index = 0;
    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        ArrayList list = map->items[i];
        for (size_t j = 0; j < list.size; j++)
        {
            all_items[index++] = list.data[j];
        }
    }

    // Sort items by count in descending order
    qsort(all_items, total_items, sizeof(ArrayListItem), compare_items_desc);

    // Print sorted items
    for (size_t i = 0; i < total_items; i++)
    {
        printf("(%zu) %s: %zu\n", strlen(all_items[i].word), all_items[i].word, all_items[i].count);
    }

    free(all_items);
}
