#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "array_list.h"
#include "read_file.h"

char *clean_word(char *word);

WordList *read_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL; // File could not be opened
    }

    WordList *word_list = malloc(sizeof(WordList));
    if (word_list == NULL)
    {
        fclose(file);
        return NULL; // Memory allocation failed
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE - 1, file)) > 0)
    {
        buffer[bytes_read] = '\0';
        char *word = strtok(buffer, " \n");
        while (word != NULL)
        {
            if (word_list->count < MAX_WORD_COUNT)
            {
                char *cleaned_word = clean_word(word);
                word = strtok(NULL, " \n");

                if (cleaned_word[strlen(cleaned_word) - 1] == '-')
                {
                    word = strncat(cleaned_word, word, MAX_WORD_LENGTH);
                    cleaned_word = clean_word(word);
                    word = strtok(NULL, " \n");
                }

                if (cleaned_word == NULL || strlen(cleaned_word) == 0)
                {
                    free(cleaned_word);
                    continue;
                }

                strncpy(word_list->words[word_list->count], cleaned_word, MAX_WORD_LENGTH - 1);
                word_list->words[word_list->count][MAX_WORD_LENGTH - 1] = '\0'; // Ensure null termination
                word_list->count++;
                free(cleaned_word);
            }
            else
            {
                fprintf(stderr, "Maximum word count reached. Some words may not be stored.\n");
                break;
            }
        }
    }

    fclose(file);
    return word_list;
}

char *clean_word(char *word)
{
    // Remove punctuation and convert to lowercase
    char *cleaned = malloc(strlen(word) + 1);
    if (cleaned == NULL)
    {
        return NULL; // Memory allocation failed
    }

    char *ptr = cleaned;
    for (const char *p = word; *p != '\0'; p++)
    {
        if (isalpha(*p))
        {
            *ptr++ = tolower(*p);
        }
    }
    *ptr = '\0'; // Null-terminate the cleaned string

    return cleaned;
}
