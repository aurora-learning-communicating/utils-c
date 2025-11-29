#include "optional.h"
#include "logs.h"
#include <assert.h>
#include <string.h>

struct Optional optional_init(void * data, size_t element_size,
                 void (*free_fn)(void *)) {
    struct Optional option = {
        .is_present = data != NULL,
        .data = data,
        .element_size = element_size,
        .free = free_fn
    };
    
    return option;
}

bool optional_is_present(struct Optional * option) {
    assert(option != NULL);
    return option->is_present;
}

bool optional_is_empty(struct Optional * option) {
    assert(option != NULL);
    return !(option->is_present);
}

void optional_get(struct Optional * option, void * ptr) {
    assert(option != NULL);
    assert(ptr != NULL);
    assert(optional_is_present(option));

    memcpy(ptr, option->data, option->element_size);
}

void optional_free(struct Optional * option) {
    assert(option != NULL);
    if (option->free != NULL) {
        (option->free)(option->data);
    }
}

void optional_panic(struct Optional * option, struct LogTrace * trace) {
    assert(option != NULL);
    assert(trace != NULL);

    if (!option -> is_present) {
        optional_free(option);

        panic_with(trace, "optional panic");
    }
}