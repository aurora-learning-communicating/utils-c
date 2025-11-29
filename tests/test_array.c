#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    {
        size_t element_size = sizeof(int);
        size_t array_size = 10;
        int * pointer = malloc(element_size * array_size);
        struct Array array = array_init(pointer, array_size, element_size, free);

        int value = 0;
        for (int offset = 0; offset < array_size; offset += 1) {
            value = offset;
            array_set(&array, offset, &value);
        }

        value = 0;
        for (int offset = 0; offset < array_size; offset += 1) {
            array_get(&array, offset, &value);
            printf("now value is %d\n", value);
        }


        array_free(&array);
    }

    {
        char * literal = "hello world";
        size_t string_length = strlen(literal);
        struct Array array = array_init(literal, string_length, sizeof(char), NULL);


        char value = 0;
        for (int offset = 0; offset < string_length; offset += 1) {
            array_get(&array, offset, &value);
            putchar(value);
            putchar('\n');
        }

        array_free(&array);
    }
}