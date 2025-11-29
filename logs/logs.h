#pragma once

struct LogTrace {
    const char * func;
    const char * file;
    unsigned int line;
};

void panic_with(struct LogTrace * trace, const char * literal);

#define CURRENT_LOGGING \
    {.func = __FUNCTION__, .line = __LINE__, .file = __FILE__}