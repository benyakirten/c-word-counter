#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
