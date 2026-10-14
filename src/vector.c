#include "vector.h"
#include <stdint.h>
#include <stdlib.h>

int vector_init(Vector *v) {
    if (v == NULL) {
        return -1;
    }

    v->data = NULL;
    v->capacity = 0;
    v->size = 0;

    return 0;
}

void vector_destroy(Vector *v) {
    if (v == NULL) {
        return;
    }

    free(v->data);

    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

int vector_reserve(Vector *v, size_t capacity) {
    if (v == NULL) {
        return -1;
    }

    if (v->capacity >= capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    int *tmp = realloc(v->data, capacity * sizeof(int));

    if (tmp == NULL) {
        return -1;
    }

    v->data = tmp;
    v->capacity = capacity;

    return 0;
}

int vector_push(Vector *v, int value) {
    if (v == NULL) {
        return -1;
    }

    if (v->size == v->capacity) {
        size_t new_capacity;

        if (v->capacity == 0) {
            new_capacity = 4;
        } else {
            if (v->capacity > SIZE_MAX / sizeof(int) / 2) {
                return -1;
            }

            new_capacity = v->capacity * 2;
        }

        if (vector_reserve(v, new_capacity) != 0) {
            return -1;
        }
    }

    v->data[v->size] = value;
    v->size++;

    return 0;
}

int vector_pop(Vector *v, int *out) {
    if (v == NULL || out == NULL || v->size == 0) {
        return -1;
    }

    v->size--;
    *out = v->data[v->size];

    return 0;
}

int vector_get(const Vector *v, size_t index, int *out) {
    if (v == NULL || out == NULL) {
        return -1;
    }

    if (index >= v->size) {
        return -1;
    }

    *out = v->data[index];

    return 0;
}

int vector_set(Vector *v, size_t index, int value) {
    if (v == NULL) {
        return -1;
    }

    if (index >= v->size) {
        return -1;
    }

    v->data[index] = value;

    return 0;
}

void vector_clear(Vector *v) {
    if (v == NULL) {
        return;
    }

    v->size = 0;
}

int vector_resize(Vector *v, size_t new_size) {
    if (v == NULL) {
        return -1;
    }

    if (new_size > v->capacity) {
        if (vector_reserve(v, new_size) != 0) {
            return -1;
        }
    }

    for (size_t i = v->size; i < new_size; i++) {
        v->data[i] = 0;
    }

    v->size = new_size;

    return 0;
}
