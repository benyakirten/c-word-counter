#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashmap.h"
#include "array_list.h"
#include "words.h"

#define FILE_READ_BUFFER_SIZE 1024
#define MAX_WORD_LENGTH 100

int hash(char *key)
{
    int hash = 0;
    while (*key)
    {
        hash = (hash << 0b101) - hash + (unsigned char)(*key++);
    }
    if (hash < 0)
    {
        hash = -hash; // Ensure hash is non-negative
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

    return map;
}

Hashmap *hashmap_from_file(char *path)
{
    Hashmap *map = hashmap_new();
    if (map == NULL)
    {
        return NULL; // Memory allocation failed
    }

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        return NULL; // File could not be opened
    }

    char buffer[FILE_READ_BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), FILE_READ_BUFFER_SIZE - 1, file)) > 0)
    {
        buffer[bytes_read] = '\0';
        char *word = strtok(buffer, " \n");

        while (word != NULL)
        {
            char *cleaned_word = clean_word(word);
            word = strtok(NULL, " \n");

            if (cleaned_word[strlen(cleaned_word) - 1] == '-')
            {
                word = strncat(cleaned_word, word, MAX_WORD_LENGTH);
                cleaned_word = clean_word(word);
                word = strtok(NULL, " \n");
            }

            if (cleaned_word[strlen(cleaned_word) - 1] == '-')
            {
                word = strncat(cleaned_word, word, MAX_WORD_LENGTH);
                cleaned_word = clean_word(word);
                word = strtok(NULL, " \n");
            }

            if (cleaned_word == NULL)
            {
                break;
            }

            if (strlen(cleaned_word) == 0)
            {
                continue;
            }

            hashmap_insert(map, cleaned_word);
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
            ArrayList *array_list = map->items[i];
            array_list_free(array_list);
        }
        free(map);
    }
}

size_t *hashmap_get(Hashmap *map, char *word)
{
    int hash_value = hash(word);
    ArrayList *array_list = map->items[hash_value];

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
    ArrayList *array_list = map->items[hash_value];
    if (array_list == NULL)
    {
        array_list = array_list_new(NULL);
        if (array_list == NULL)
        {
            return false; // Memory allocation failed
        }
        map->items[hash_value] = array_list; // Store the new ArrayList in the hashmap
    }

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
    ArrayList *array_list = map->items[hash_value];

    if (array_list == NULL || array_list == NULL)
    {
        return false; // No list found for this hash value
    }

    return array_list_remove(array_list, word);
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

void hashmap_print(Hashmap *map)
{
    // First, count total number of items
    size_t total_items = 0;
    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        ArrayList *list = map->items[i];
        if (list != NULL)
        {
            total_items += list->size;
        }
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
        ArrayList *list = map->items[i];
        if (list == NULL)
            continue; // Skip empty lists

        for (size_t j = 0; j < list->size; j++)
        {
            all_items[index++] = list->data[j];
        }
    }

    // Sort items by count in descending order
    qsort(all_items, total_items, sizeof(ArrayListItem), compare_items_desc);

    // Print sorted items
    printf("Total unique words: %zu\n", total_items);
    for (size_t i = 0; i < total_items; i++)
    {
        printf("(#%zu) %s: %zu\n", i + 1, all_items[i].word, all_items[i].count);
    }

    free(all_items);
}
