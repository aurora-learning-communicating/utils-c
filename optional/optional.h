#pragma once

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

struct Optional optional_init(void * data, size_t element_size, FreeFn free_fn);

bool optional_is_present(struct Optional * option);
bool optional_is_empty(struct Optional * option);

void optional_get(struct Optional * option, void * ptr);
void optional_free(struct Optional * option);
void optional_panic(struct Optional * option, struct LogTrace * trace);