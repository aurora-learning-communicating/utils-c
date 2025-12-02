#include "list.h"
#include "optional.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct ListNode listnode_init(void * data) {
    assert(data != NULL);

    struct ListNode node = {
        .data = data,
        .prev = NULL,
        .next = NULL
    };

    return node;
}

void listnode_insert_next(struct ListNode * node, struct ListNode * target) {
    assert(node != NULL);
    assert(target != NULL);

    struct ListNode * next_node = node -> next;
    node -> next = target;
    target -> prev = node;

    target -> next = next_node;

    if (next_node != NULL) {
        next_node -> prev = target;
    }
}

void listnode_remove_next(struct ListNode * node) {
    assert(node != NULL);

    struct ListNode * next_node = node -> next;

    if (next_node == NULL) {
        return;
    }

    struct ListNode * next_next_node = next_node -> next;
    node -> next = next_next_node;

    if (next_next_node != NULL) {
        next_next_node -> prev = node;
    }

    free(next_node);
}

struct List list_init(FreeFn free, size_t element_size) {
    struct List list = {
        .free = free,
        .head = NULL,
        .tail = NULL,
        .element_size = element_size,
        .length = 0
    };

    return list;
}

void list_free(struct List * list) {
    assert(list != NULL);

    struct ListNode * current = list -> head;
    struct ListNode * prev = NULL;

    while (current != NULL) {
        if (list -> free != NULL) {
            (list -> free) (current -> data);
        }

        prev = current;
        current = current -> next;
        free(prev);
    }
}

void list_push(struct List * list, void * data) {
    assert(list != NULL);
    assert(data != NULL);

    struct ListNode * new_node = malloc(sizeof(struct ListNode));
    *new_node = listnode_init(data);

    if (list -> head == NULL) { // is empty
        list -> head = new_node;
        list -> tail = new_node;
    } else {
        listnode_insert_next(list -> tail, new_node);
        list -> tail = list -> tail -> next;
    }

    list -> length += 1;
}

bool list_is_empty(struct List * list) {
    assert(list != NULL);

    return list -> length == 0;
}

void list_push_first(struct List * list, void * data) {
    assert(list != NULL);
    assert(data != NULL);

    struct ListNode * new_node = malloc(sizeof(struct ListNode));
    *new_node = listnode_init(data);

    if (list -> head == NULL) {
        list -> head = new_node;
        list -> tail = new_node;
    } else {
        new_node -> next = list -> head;
        list -> head -> prev = new_node;
        list -> head = new_node;
    }

    list -> length += 1;
}

struct Optional list_pop(struct List * list) {
    // 需要 注意 删除后 为空的情况
    struct Optional pop_result = optional_init(list -> element_size, list -> free);
    
    if (list -> tail == NULL) {
        optional_from(&pop_result, NULL);
        return pop_result;
    }

    struct ListNode * prev_tail = list -> tail -> prev;
    optional_from(&pop_result, list -> tail -> data);
    free(list -> tail);

    // 前移 list -> tail
    list -> tail = prev_tail;

    if (list -> tail == NULL) { // 删除后为空
        list -> head = NULL;
    } else {
        list -> tail -> next = NULL;
    }

    list -> length -= 1;
    return pop_result;
}

struct Optional list_pop_first(struct List * list) {
    // 需要 注意 删除后 为空的情况
    struct Optional pop_result = optional_init(list -> element_size, list -> free);

    if (list -> tail == NULL) {
        optional_from(&pop_result, NULL);
        return pop_result;
    }

    struct ListNode * next_head = list -> head -> next;
    optional_from(&pop_result, list -> head -> data);
    free(list -> head);

    // list -> head 后移
    list -> head = next_head;

    if (list -> head == NULL) {
        list -> tail = NULL;
    } else {
        list -> head -> prev = NULL;
    }

    list -> length -= 1;
    return pop_result;
}

void list_pop_if(struct List * list, Predicate predicate, void * closure_data) {
    assert(list != NULL);
    assert(predicate != NULL);

    struct ListNode * current = list -> head;

    while (current != NULL) {
        void * data = current -> data;
        if (!predicate(data, closure_data)) {
            current = current -> next;
            continue;
        }


        if (current == list -> head) {
            current = current -> next;
            list_pop_first(list);
        } else if (current == list -> tail) {
            current = current -> next;
            list_pop(list);
        } else {
            struct ListNode * prev = current -> prev;
            current = current -> next;
            if (list -> free != NULL) {
                (list -> free) (current -> data);
            }

            listnode_remove_next(prev);
            list -> length -= 1;
        }
        
    }

}

// Optional<Data>, not pointer
struct Optional list_find_first(struct List * list, Predicate predicate, void * closure_data) {
    assert(list != NULL);
    assert(predicate != NULL);
    // sizeof data
    size_t element_size = list -> element_size;

    struct Optional find_result = optional_init(element_size, NULL);

    if (list -> length == 0) {
        optional_from(&find_result, NULL);
        return find_result;
    }

    struct ListIterator iterator = list_iterate_init(list);
    struct Optional next;
    struct Array buffer;
    
    while (true) {
        next = list_iterate_next(&iterator);
        if (optional_is_empty(&next)) {
            break;
        }

        buffer = optional_get(&next);
        if (predicate(buffer.data, closure_data)) {
            optional_from(&find_result, buffer.data);
            break;
        }
    }


    return find_result;
}

struct ListIterator list_iterate_init(struct List * list) {
    assert(list != NULL);
    struct ListIterator iterator = {
        .list = list,
        .current = list -> head,
    };

    return iterator;
}

struct Optional list_iterate_next(struct ListIterator * iterator) {
    assert(iterator != NULL);
    assert(iterator -> list != NULL);

    struct Optional next = optional_init(iterator -> list -> element_size, NULL);
    struct ListNode * current = iterator -> current;

    if (current != NULL) {
        optional_from(&next, current -> data);
    } else {
        optional_from(&next, NULL);
    }
    

    if (current != NULL) {
        iterator -> current = current -> next;
    }

    return next;
}