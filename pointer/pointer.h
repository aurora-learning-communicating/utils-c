#pragma once

#include "logs.h"
#include <stddef.h>

typedef void (*FreeFn) (void *);

struct Pointer {
    void * pointer;
    FreeFn free;
    size_t pointer_size;
};

struct Pointer pointer_init(void * ptr, FreeFn free_fn);
void pointer_free(struct Pointer * pointer);

void nullable_get(struct Pointer * pointer, void ** dest);
void nonnull_get(struct Pointer * pointer, void ** dest, struct LogTrace * trace);