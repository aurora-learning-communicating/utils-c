#pragma once

#include <stddef.h>

typedef void (*FreeFn) (void *);

struct Array {
    void * data;
    size_t length; // 数组长度
    size_t element_size;
    FreeFn free;
};

struct Array array_init(void * data, size_t length,
                size_t element_size, void (*free_fn)(void *));
void array_get(struct Array * array, size_t offset, void * ptr);
void array_set(struct Array * array, size_t offset, void * ptr_source);
void array_free(struct Array * array);

size_t array_length(struct Array * array);