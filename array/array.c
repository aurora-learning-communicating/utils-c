#include "array.h"

#include <assert.h>
#include <string.h>

struct Array array_init(void * data, size_t length, size_t element_size, FreeFn free) {
    assert(data != NULL);

    struct Array array = {
        .data = data,
        .length = length,
        .element_size = element_size,
        .free = free
    };
    
    return array;
}

void array_get(struct Array * array, size_t offset, void * ptr) {
    assert(array != NULL);
    assert(ptr != NULL);

    assert(offset >= 0 && offset <= array->length - 1);

    char * data_start = array->data;
    memcpy(ptr, data_start + offset * (array->element_size),
           array->element_size);
}

void array_set(struct Array * array, size_t offset, void * ptr_source) {
    assert(array != NULL);
    assert(ptr_source != NULL);

    assert(offset >= 0 && offset <= array->length - 1);

    char * data_start = array->data;
    char * ptr = data_start + offset * (array->element_size);
    memcpy(ptr, ptr_source, array->element_size);
}

void array_free(struct Array * array) {
    assert(array != NULL);

    if (array -> free != NULL) {
        (array -> free)(array -> data);
    }
}

size_t array_length(struct Array * array) {
    assert(array != NULL);

    return array -> length;
}