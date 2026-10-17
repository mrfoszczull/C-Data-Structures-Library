#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Singly linked list of integers.
 *
 * Elements are indexed starting from 0.
 * Initialize a list with list_init() before using it.
 * Do not modify the structure's fields directly.
 */
typedef struct ListNode {
    int data;              // Value stored in the node
    struct ListNode *next; // Pointer to the next node, or NULL
} ListNode;

typedef struct {
    ListNode *head; // First node, or NULL if the list is empty
    size_t size;    // Number of elements in the list
} List;

/*
 * Initializes an empty list.
 * Returns 0 on success, -1 if l is NULL.
 */
int list_init(List *l);

/*
 * Frees all nodes owned by the list.
 * Does nothing if l is NULL.
 * The list must be initialized again before reuse.
 */
void list_destroy(List *l);

/*
 * Inserts an element at the beginning or end of the list.
 * Returns 0 on success, -1 if l is NULL or memory allocation fails.
 */
int list_push_front(List *l, int num);
int list_push_back(List *l, int num);

/*
 * Removes the first or last element of the list.
 * Stores the removed value in *out.
 * Returns 0 on success, -1 if the list is empty or an argument is invalid.
 */
int list_pop_front(List *l, int *out);
int list_pop_back(List *l, int *out);

/*
 * Reads or updates the element at the given index.
 * list_get() stores the value in *out.
 * list_set() replaces the existing value.
 * Returns 0 on success, -1 if an argument is invalid or the index is out of
 * range.
 */
int list_get(const List *l, size_t index, int *out);
int list_set(List *l, size_t index, int num);

/*
 * Inserts or removes an element at the given index.
 *
 * list_insert() accepts indices from 0 to list_size(l), inclusive.
 * list_remove() accepts indices from 0 to list_size(l) - 1.
 * list_remove() stores the removed value in *out.
 *
 * Returns 0 on success, -1 if an argument is invalid, the index is out of
 * range, or memory allocation fails during insertion.
 */
int list_insert(List *l, size_t index, int num);
int list_remove(List *l, size_t index, int *out);

/*
 * Returns the number of elements in the list.
 * Returns 0 if the list is empty.
 */
size_t list_size(const List *l);

/*
 * Returns true if the list is empty, otherwise false.
 */
bool list_is_empty(const List *l);

/*
 * Removes all elements and frees their nodes.
 * The list remains initialized and can be reused.
 * Returns 0 on success, -1 if l is NULL.
 */
int list_clear(List *l);

#endif
