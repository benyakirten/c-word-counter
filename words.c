#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "array_list.h"
#include "words.h"

char *clean_word(char *word)
{
    // Remove punctuation and convert to lowercase
    char *cleaned = malloc(WORD_MAX_LENGTH * sizeof(char));
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
