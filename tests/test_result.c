#include "array.h"
#include "logs.h"
#include "result.h"
#include <stdio.h>

int main() {
    struct ResultOption option_ok = {
        .element_size = sizeof(int),
        .free = NULL
    };

    struct ResultOption option_err = {
        .element_size = sizeof(int),
        .free = NULL
    };

    struct Result result = result_init(option_ok, option_err);
    int ok = 1;
    result_ok(&result, &ok);

    int err = 1;
    result_err(&result, &err);

    struct LogTrace trace = CURRENT_LOGGING;
    result_panic(&result, &trace);

    result_free(&result);
}