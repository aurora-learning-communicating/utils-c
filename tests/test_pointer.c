#include "logs.h"
#include "pointer.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    {    
        size_t malloc_size = sizeof(int) * 10;
        int * ptr = malloc(malloc_size);

        ptr[0] = 10;

        struct Pointer pointer = pointer_init(ptr, free, sizeof(int));

        int * dest;
        struct LogTrace trace = CURRENT_LOGGING;
        nonnull_get(&pointer, &dest, &trace);
        printf("dest 0: %d\n", dest[0]);

        pointer_free(&pointer);
    }    

    {
        int * ptr = NULL;

        struct Pointer pointer = pointer_init(ptr, NULL, sizeof(int));

        int * dest;
        struct LogTrace trace = CURRENT_LOGGING;
        nonnull_get(&pointer, &dest, &trace);

        pointer_free(&pointer);
    }
}