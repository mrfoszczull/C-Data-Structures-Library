#include "../include/stack.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int stack_init(Stack *s, size_t element_size) {
    if (s == NULL || element_size == 0) {
        return -1;
    }

    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
    s->element_size = element_size;

    return 0;
}

void stack_destroy(Stack *s) {
    if (s == NULL) {
        return;
    }

    free(s->data);
    s->data = NULL;
    s->element_size = 0;
    s->size = 0;
    s->capacity = 0;
}

int stack_push(Stack *s, const void *element) {
    if (s == NULL || element == NULL) {
        return -1;
    }

    if (s->size == s->capacity) {
        size_t new_capacity;

        if (s->capacity == 0) {
            new_capacity = 4;
        } else {
            if (s->capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = s->capacity * 2;
        }

        if (new_capacity > SIZE_MAX / s->element_size) {
            return -1;
        }

        void *tmp = realloc(s->data, new_capacity * s->element_size);

        if (tmp == NULL) {
            return -1;
        }

        s->data = tmp;
        s->capacity = new_capacity;
    }

    unsigned char *destination =
        (unsigned char *)s->data + s->size * s->element_size;
    memcpy(destination, element, s->element_size);
    s->size++;

    return 0;
}

int stack_pop(Stack *s, void *value) {
    if (s == NULL || value == NULL || s->size == 0) {
        return -1;
    }

    unsigned char *top =
        (unsigned char *)s->data + (s->size - 1) * s->element_size;

    memcpy(value, top, s->element_size);
    s->size--;

    return 0;
}

int stack_peek(const Stack *s, void *value) {
    if (s == NULL || value == NULL || s->size == 0) {
        return -1;
    }

    const unsigned char *top =
        (const unsigned char *)s->data + (s->size - 1) * s->element_size;

    memcpy(value, top, s->element_size);

    return 0;
}

size_t stack_size(const Stack *s) {
    if (s == NULL) {
        return 0;
    }

    return s->size;
}

bool stack_is_empty(const Stack *s) {
    if (s == NULL || s->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void stack_clear(Stack *s) {
    if (s == NULL) {
        return;
    }

    s->size = 0;
}
