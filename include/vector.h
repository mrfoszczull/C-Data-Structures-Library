#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

int vector_init(Vector *v);
void vector_destroy(Vector *v);

int vector_push(Vector *v, int value);
int vector_pop(Vector *v, int *out);

int vector_get(const Vector *v, size_t index, int *out);
int vector_set(Vector *v, size_t index, int value);

int vector_reserve(Vector *v, size_t capacity);
int vector_resize(Vector *v, size_t new_size);

void vector_clear(Vector *v);

#endif
