#include "array.h"
#include "list.h"
#include "optional.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static bool isequal(void * data, void * user_data);
static bool isless(void * data, void * user_data);
static bool isgreater(void * data, void * user_data);
int main() {
    /** test:
        void list_push(struct List * list, void * data);
        void list_push_first(struct List * list, void * data);
        struct Optional list_pop(struct List * list);
        struct Optional list_pop_first(struct List * list);
        void list_pop_at(struct List * list, struct ListIterator * iteartor);
        void list_push_next(struct List * list, struct ListIterator * iterator, void * data);
        struct Optional list_find_first(struct List * list, Predicate predicate, void * closure_data);
        bool list_is_empty(struct List * list);

        struct ListIterator list_iterate_init(struct List * list);
        struct Optional list_iterate_next(struct ListIterator * iterator);
    */

    {
        struct List list = list_init(free, sizeof(int));

        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push(&list, value);
        }

        struct ListIterator iterator = list_iterate_init(&list);
        struct Optional next = list_iterate_next(&iterator);

        struct Array buffer;
        
        while (optional_is_present(&next)) {
            buffer = optional_get(&next);

            printf("value is %d\n", *(int *)(buffer.data));
            next = list_iterate_next(&iterator);
        }

        list_free(&list);
    }

    {
        struct List list = list_init(free, sizeof(int));
        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push_first(&list, value);
        }

        struct ListIterator iterator = list_iterate_init(&list);
        struct Optional next = list_iterate_next(&iterator);

        struct Array buffer;
        
        while (optional_is_present(&next)) {
            buffer = optional_get(&next);

            printf("value is %d\n", *(int *)(buffer.data));
            next = list_iterate_next(&iterator);
        }
        
        list_free(&list);
    }

    {
        struct List list = list_init(free, sizeof(int));

        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push(&list, value);
        }

        struct Optional pop_result;
        struct Array buffer;
        // try pop until empty
        pop_result = list_pop(&list);
        while (optional_is_present(&pop_result)) {
            buffer = optional_get(&pop_result);
            printf("pop: %d\n", *(int *) (buffer.data));
            pop_result = list_pop(&list);
        }
        
        
        printf("now is empty: %d\n", list_is_empty(&list));
        list_free(&list);
    }

    {
        struct List list = list_init(free, sizeof(int));

        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push(&list, value);
        }

        struct Optional pop_result;
        struct Array buffer;
        // try pop until empty
        pop_result = list_pop_first(&list);
        while (optional_is_present(&pop_result)) {
            buffer = optional_get(&pop_result);
            printf("pop: %d\n", *(int *) (buffer.data));
            pop_result = list_pop_first(&list);
        }
        
        
        printf("now is empty: %d\n", list_is_empty(&list));
        list_free(&list);
    }

    {
        struct List list = list_init(free, sizeof(int));

        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push(&list, value);
        }

        int pivot = 5;
        struct Optional option = list_find_first(&list, isequal, &pivot);

        if (optional_is_present(&option)) {
            struct Array array = optional_get(&option);
            printf("predicate: %d\n", *(int *) (array.data));
            array_free(&array);
        }

        optional_free(&option);
        list_free(&list);
    }

    {
        struct List list = list_init(free, sizeof(int));

        int * value = NULL;
        for (int start = 0; start <= 10; start += 1) {
            value = malloc(sizeof(int));
            *value = start;

            list_push(&list, value);
        }

        int pivot = 5;
        list_pop_if(&list, isless, &pivot);

        struct ListIterator iterator = list_iterate_init(&list);
        struct Optional next = list_iterate_next(&iterator);

        struct Array buffer;

        puts("after pop if");
        while (optional_is_present(&next)) {
            buffer = optional_get(&next);

            printf("value is %d\n", *(int *)(buffer.data));
            next = list_iterate_next(&iterator);
        }

        
        pivot = 4;
        list_pop_if(&list, isgreater, &pivot);
        iterator = list_iterate_init(&list);
        next = list_iterate_next(&iterator);

        puts("after pop if");
        while (optional_is_present(&next)) {
            buffer = optional_get(&next);

            printf("value is %d\n", *(int *)(buffer.data));
            next = list_iterate_next(&iterator);
        }

        list_free(&list);
    }   
}

bool isequal(void * data, void * user_data) {
    int left = *(int *) data;
    int right = *(int *) user_data;
    
    return left == right;
}

bool isless(void * data, void * user_data) {
    int left = *(int *) data;
    int right = *(int *) user_data;

    return left < right;
}

bool isgreater(void * data, void * user_data) {
    int left = *(int *) data;
    int right = *(int *) user_data;

    return left > right;
}