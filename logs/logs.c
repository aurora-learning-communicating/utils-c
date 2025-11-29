#include "logs.h"
#include <stdio.h>
#include <stdlib.h>

void panic_with(struct LogTrace * trace, const char * literal) {
    fprintf(stderr, "error at %s:%s:%d, %s\n", trace -> file,
                trace -> func, trace -> line, literal);

    exit(EXIT_FAILURE);
}