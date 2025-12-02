#include "optional.h"
#include "array.h"
#include "logs.h"
#include <assert.h>
#include <string.h>

struct Optional optional_init(size_t element_size,
                 void (*free_fn)(void *)) {
    struct Optional option = {
        .is_present = false,
        .data = NULL,
        .element_size = element_size,
        .free = free_fn
    };
    
    return option;
}

void optional_from(struct Optional * option, void * data) {
    assert(option != NULL);
    option -> data = data;
    option -> is_present = data != NULL;

    if (!option -> is_present) {
        option -> free = NULL;
    }
}


bool optional_is_present(struct Optional * option) {
    assert(option != NULL);
    return option->is_present;
}

bool optional_is_empty(struct Optional * option) {
    assert(option != NULL);
    return !(option->is_present);
}

struct Array optional_get(struct Optional * option) {
    assert(option != NULL);
    assert(optional_is_present(option));

    struct Array array = array_init(option -> data, option -> element_size, sizeof(char), NULL);

    return array;
    // *ptr = option -> data;
    // memcpy(*ptr, option -> data, option -> element_size);
    // memcpy(ptr, option->data, option->element_size);
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