#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

/*
 * Dynamic array of integers.
 *
 * Elements are indexed starting from 0.
 * Initialize a vector with vector_init() before using it.
 * Do not modify the structure's fields directly.
 */
typedef struct {
    int *data;       // Pointer to the allocated memory buffer
    size_t size;     // Number of elements currently stored
    size_t capacity; // Number of elements that can fit in the buffer
} Vector;

/*
 * Initializes an empty vector.
 * Returns 0 on success, -1 if v is NULL.
 */
int vector_init(Vector *v);

/*
 * Frees the allocated memory and resets the vector.
 * Does nothing if v is NULL.
 * The vector must be initialized again before reuse.
 */
void vector_destroy(Vector *v);

/*
 * Appends an element to the end of the vector.
 * Capacity grows automatically if needed.
 * Returns 0 on success, -1 if an argument is invalid or allocation fails.
 */
int vector_push(Vector *v, int value);

/*
 * Removes the last element and stores its value in *out.
 * Returns 0 on success, -1 if the vector is empty or an argument is invalid.
 */
int vector_pop(Vector *v, int *out);

/*
 * Reads or updates the element at the given index.
 * vector_get() stores the value in *out.
 * vector_set() replaces the existing value.
 * Returns 0 on success, -1 if an argument is invalid or the index is out of
 * range.
 */
int vector_get(const Vector *v, size_t index, int *out);
int vector_set(Vector *v, size_t index, int value);

/*
 * Ensures that the vector can hold at least the requested number of elements.
 * Existing elements are preserved.
 * The size does not change.
 * Returns 0 on success, -1 if an argument is invalid or allocation fails.
 */
int vector_reserve(Vector *v, size_t capacity);

/*
 * Changes the number of elements in the vector.
 * If the size increases, new elements are initialized to zero.
 * If the size decreases, elements beyond the new size are discarded.
 * Returns 0 on success, -1 if an argument is invalid or allocation fails.
 */
int vector_resize(Vector *v, size_t new_size);

/*
 * Removes all elements by setting size to 0.
 * Keeps the allocated memory for reuse.
 * Does nothing if v is NULL.
 */
void vector_clear(Vector *v);

#endif
