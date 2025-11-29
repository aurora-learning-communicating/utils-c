#include <stdio.h>

void logging(const char * literal) {
    printf("line: %d, func: %s, message: %s\n", __LINE__, __FUNCTION__,
           literal);
}

int main() { logging("hello"); }
