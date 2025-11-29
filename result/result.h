#pragma once

#include "logs.h"
#include <stdbool.h>
#include <stddef.h>

typedef void (*FreeFn) (void *);

struct ResultOption {
    size_t element_size;
    FreeFn free;
};

struct Result {
    bool is_ok;

    union {
        void * ok;
        void * err;
    };

    struct ResultOption option_ok, option_err;
};

bool result_is_ok(struct Result * result);
bool result_is_err(struct Result * result);

struct Result result_init(struct ResultOption ok, struct ResultOption err);

void result_ok(struct Result * result, void * data);
void result_err(struct Result * result, void * data);

void result_get_ok(struct Result * result, void * dest);
void result_get_err(struct Result * result, void * dest);

void result_free(struct Result * result);

void result_panic(struct Result * result, struct LogTrace * trace);