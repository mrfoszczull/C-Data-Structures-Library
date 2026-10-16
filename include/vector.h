#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Dynamic array structure for integers
typedef struct {
    int *data;       // Pointer to the allocated memory buffer
    size_t size;     // Current number of elements
    size_t capacity; // Maximum capacity before reallocation
} Vector;

// Initializes an empty vector. Returns 0 on success, or -1 on error.
int vector_init(Vector *v);

// Frees the allocated memory and resets vector fields.
void vector_destroy(Vector *v);

// Appends an element to the end of the vector. Returns 0 on success, -1 on
// error.
int vector_push(Vector *v, int value);

// Removes the last element and stores it in 'out'. Returns 0 on success, -1 on
// error.
int vector_pop(Vector *v, int *out);

// Retrieves the element at 'index' into 'out'. Returns 0 on success, -1 if
// index is out of bounds.
int vector_get(const Vector *v, size_t index, int *out);

// Sets the value at 'index'. Returns 0 on success, -1 if index is out of
// bounds.
int vector_set(Vector *v, size_t index, int value);

// Pre-allocates memory to fit at least 'capacity' elements. Returns 0 on
// success, -1 on error.
int vector_reserve(Vector *v, size_t capacity);

// Resizes the vector to 'new_size'. New elements are initialized to zero.
// Returns 0 on success, -1 on error.
int vector_resize(Vector *v, size_t new_size);

// Clears the vector content by setting size to 0 (does not free memory).
void vector_clear(Vector *v);

#endif
