#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {

        Hashmap *map = hashmap_from_file(argv[i]);
        if (map == NULL)
        {
            fprintf(stderr, "Failed to create hashmap from words.\n");
            return 1; // Exit with error
        }

        printf("Word count for file %s:\n", argv[i]);

        hashmap_print(map);
        hashmap_free(map);
    }
}
