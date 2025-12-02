#pragma once

#include "array.h"
#include "logs.h"

#include <stdbool.h>
#include <stddef.h>

typedef void (*FreeFn)(void *);

struct Optional {
    bool is_present;
    void * data;
    size_t element_size;
    FreeFn free;
};

struct Optional optional_init(size_t element_size, FreeFn free_fn);
void optional_from(struct Optional * option, void * data);

bool optional_is_present(struct Optional * option);
bool optional_is_empty(struct Optional * option);

// return a uint8_t array, aka char[]
struct Array optional_get(struct Optional * option);
void optional_free(struct Optional * option);
void optional_panic(struct Optional * option, struct LogTrace * trace);