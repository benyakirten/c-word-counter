#include <stddef.h>
#include <stdio.h>

#ifndef READFILE_H
#define READFILE_H

#define BUFFER_SIZE 1024 * 100
#define MAX_WORD_LENGTH 101
#define MAX_WORD_COUNT 1024 * 200

typedef struct
{
    char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];
    size_t count;
} WordList;

WordList *read_file(char *filename);

#endif
