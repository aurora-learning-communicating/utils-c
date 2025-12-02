#pragma once

#include "optional.h"
#include <stdbool.h>

typedef void (*FreeFn) (void *);
typedef bool (*Predicate)(void *, void *);

struct ListNode {
    void * data;
    struct ListNode * next;
    struct ListNode * prev;
};

struct List {
    struct ListNode * head;
    struct ListNode * tail;

    size_t element_size;
    int length;
    FreeFn free;
};

struct ListIterator {
    struct List * list;
    struct ListNode * current;
};

struct ListNode listnode_init(void * data);
void listnode_insert_next(struct ListNode * node, struct ListNode * target);
void listnode_remove_next(struct ListNode * node);

struct List list_init(FreeFn free, size_t element_size);
void list_free(struct List * list);

void list_push(struct List * list, void * data);
void list_push_first(struct List * list, void * data);
struct Optional list_pop(struct List * list);
struct Optional list_pop_first(struct List * list);
void list_pop_if(struct List * list, Predicate predicate, void * closure_data);
struct Optional list_find_first(struct List * list, Predicate predicate, void * closure_data);
bool list_is_empty(struct List * list);


struct ListIterator list_iterate_init(struct List * list);
struct Optional list_iterate_next(struct ListIterator * iterator);