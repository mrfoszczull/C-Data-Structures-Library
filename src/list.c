#include "list.h"
#include <stdlib.h>

int list_init(List *l) {
    if (l == NULL) {
        return -1;
    }

    l->size = 0;
    l->head = NULL;
    l->tail = NULL;

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
    l->tail = NULL;
    l->size = 0;

    return 0;
}

void list_destroy(List *l) {
    if (l == NULL) {
        return;
    }

    list_clear(l);
}

int list_push_front(List *l, int value) {
    if (l == NULL) {
        return -1;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = value;
    new_node->next = l->head;
    l->head = new_node;

    if (l->tail == NULL) {
        l->tail = new_node;
    }

    l->size++;

    return 0;
}

int list_push_back(List *l, int value) {
    if (l == NULL) {
        return -1;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (l->tail == NULL) {
        l->head = new_node;
        l->tail = new_node;
    } else {
        l->tail->next = new_node;
        l->tail = new_node;
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

    if (l->head == NULL) {
        l->tail = NULL;
    }

    return 0;
}

int list_pop_back(List *l, int *out) {
    if (l == NULL || out == NULL || l->head == NULL) {
        return -1;
    }

    ListNode *current = l->head;
    ListNode *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    *out = current->data;

    if (prev == NULL) {
        l->head = NULL;
        l->tail = NULL;
    } else {
        prev->next = NULL;
        l->tail = prev;
    }

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

int list_set(List *l, size_t index, int value) {
    if (l == NULL || index >= l->size) {
        return -1;
    }

    ListNode *current = l->head;

    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = value;

    return 0;
}

int list_insert(List *l, size_t index, int value) {
    if (l == NULL || index > l->size) {
        return -1;
    }

    if (index == 0) {
        return list_push_front(l, value);
    }

    if (index == l->size) {
        return list_push_back(l, value);
    }

    ListNode *current = l->head;

    for (size_t i = 1; i < index; i++) {
        current = current->next;
    }

    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return -1;
    }

    new_node->data = value;
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

size_t list_size(const List *l) { return l == NULL ? 0 : l->size; }

bool list_is_empty(const List *l) { return l == NULL || l->size == 0; }
