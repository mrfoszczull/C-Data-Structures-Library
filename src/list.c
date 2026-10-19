#include "list.h"
#include <stdlib.h>

int list_init(List *l) {
    if (l == NULL) {
        return -1;
    }

    l->size = 0;
    l->head = NULL;

    return 0;
}

int list_clear(List *l) {
    if (l == NULL) {
        return -1;
    }

    ListNode *current = l->head;

    while (current != NULL) {
        ListNode *next_node = current->next;
        free(current);
        current = next_node;
    }

    l->head = NULL;
    l->size = 0;

    return 0;
}

void list_destroy(List *l) {
    if (l == NULL) {
        return;
    }

    list_clear(l);
}

int list_push_front(List *l, int num) {
    if (l == NULL) {
        return -1;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = num;
    new_node->next = l->head;
    l->head = new_node;

    l->size++;

    return 0;
}

int list_push_back(List *l, int num) {
    if (l == NULL) {
        return -1;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = num;
    new_node->next = NULL;

    if (l->size == 0) {
        l->head = new_node;
    } else {
        ListNode *current = l->head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_node;
    }

    l->size++;

    return 0;
}

int list_pop_front(List *l, int *out) {
    if (l == NULL || l->head == NULL || out == NULL) {
        return -1;
    }

    ListNode *current = l->head;

    *out = current->data;
    l->head = current->next;

    free(current);
    l->size--;

    return 0;
}

int list_pop_back(List *l, int *out) {
    if (l == NULL || l->head == NULL || out == NULL) {
        return -1;
    }

    if (l->head->next == NULL) {
        *out = l->head->data;
        l->size = 0;
        free(l->head);
        l->head = NULL;

        return 0;
    }

    ListNode *current = l->head;
    ListNode *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    *out = current->data;
    prev->next = NULL;
    free(current);
    l->size--;

    return 0;
}

int list_get(const List *l, size_t index, int *out) {
    if (l == NULL || out == NULL || index >= l->size) {
        return -1;
    }

    ListNode *current = l->head;

    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    *out = current->data;

    return 0;
}

int list_set(List *l, size_t index, int num) {
    if (l == NULL || index >= l->size) {
        return -1;
    }

    ListNode *current = l->head;

    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = num;

    return 0;
}

int list_insert(List *l, size_t index, int num) {
    if (l == NULL || index > l->size) {
        return -1;
    }

    if (index == 0) {
        return list_push_front(l, num);
    }

    if (index == l->size) {
        return list_push_back(l, num);
    }

    ListNode *current = l->head;

    for (size_t i = 1; i < index; i++) {
        current = current->next;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = num;
    new_node->next = current->next;
    current->next = new_node;
    l->size++;

    return 0;
}

int list_remove(List *l, size_t index, int *out) {
    if (l == NULL || out == NULL || index >= l->size) {
        return -1;
    }

    if (index == 0) {
        return list_pop_front(l, out);
    }

    if (index == l->size - 1) {
        return list_pop_back(l, out);
    }

    ListNode *current = l->head;

    for (size_t i = 1; i < index; i++) {
        current = current->next;
    }

    ListNode *toRemove = NULL;

    toRemove = current->next;
    *out = toRemove->data;
    current->next = toRemove->next;
    free(toRemove);
    l->size--;

    return 0;
}

size_t list_size(const List *l) { return l->size; }

bool list_is_empty(const List *l) {
    if (l->size == 0) {
        return 1;
    } else {
        return 0;
    }
}
