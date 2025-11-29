#include "result.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool result_is_ok(struct Result * result) {
    assert(result != NULL);
    return result->is_ok;
}

bool result_is_err(struct Result * result) {
    assert(result != NULL);
    return !(result->is_ok);
}

struct Result result_init(struct ResultOption option_ok, struct ResultOption option_err) {
    struct Result result = {0};
    result.option_err = option_err;
    result.option_ok = option_ok;
    return result;
}

void result_ok(struct Result * result, void * data) {
    assert(result != NULL);
    assert(data != NULL);

    result->is_ok = true;
    result->ok = data;
}

void result_err(struct Result * result, void * data) {
    assert(result != NULL);
    assert(data != NULL);

    result->is_ok = false;
    result->err = data;
}

void result_get_ok(struct Result * result, void * dest) {
    assert(result != NULL);
    assert(dest != NULL);
    assert(result->is_ok);

    memcpy(dest, result -> ok, (result -> option_ok).element_size);
}

void result_get_err(struct Result * result, void * dest) {
    assert(result != NULL);
    assert(dest != NULL);
    assert(!(result->is_ok));

    memcpy(dest, result -> err, (result -> option_err).element_size);
}


void result_free(struct Result * result) {
    assert(result != NULL);

    void (*free_fn)(void *) = NULL;
    void * ptr = NULL;

    if (result->is_ok) {
        free_fn = (result->option_ok).free;
        ptr = result->ok;
    } else {
        free_fn = (result->option_err).free;
        ptr = result->err;
    }

    if (free_fn != NULL) {
        free_fn(ptr);
    }
}

void result_panic(struct Result * result, struct LogTrace * trace) {
    assert(result != NULL);
    assert(trace != NULL);

    if (result_is_err(result)) {
        result_free(result);

        panic_with(trace, "result panic");
    }
}