#include "pointer.h"

#include <assert.h>
#include <string.h>

struct Pointer pointer_init(void * ptr, FreeFn free_fn, size_t element_size) {
    struct Pointer pointer = {
        .pointer = ptr,
        .free = free_fn,
        .element_size = element_size
    };

    return pointer;
}

void pointer_free(struct Pointer * pointer) {
    assert(pointer != NULL);
    
    if (pointer -> free != NULL && pointer -> pointer != NULL) {
        (pointer -> free) (pointer -> pointer);
    }
}

void nullable_get(struct Pointer * pointer, void ** dest) {
    assert(pointer != NULL);
    assert(dest != NULL);

    void * data_ptr = pointer -> pointer;
    if (data_ptr != NULL) {
        *dest = data_ptr;
    }
}

void nonnull_get(struct Pointer * pointer, void ** dest, struct LogTrace * trace) {
    assert(pointer != NULL);
    assert(dest != NULL);
    assert(trace != NULL);

    void * data_ptr = pointer -> pointer;

    if (data_ptr == NULL) {
        panic_with(trace, "nonnull get");
    }

    *dest = data_ptr;
}