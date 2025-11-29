#pragma once

#include "logs.h"
#include <stddef.h>

typedef void (*FreeFn) (void *);

struct Pointer {
    void * pointer;
    FreeFn free;
    size_t element_size;
};

struct Pointer pointer_init(void * ptr, FreeFn free_fn, size_t element_size);
void pointer_free(struct Pointer * pointer);

void nullable_get(struct Pointer * pointer, void ** dest);
void nonnull_get(struct Pointer * pointer, void ** dest, struct LogTrace * trace);