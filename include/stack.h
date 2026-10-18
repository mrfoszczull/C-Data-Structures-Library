
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Generic LIFO stack.
 * The stack stores copies of elements of a fixed size.
 *
 * Elements are stored as raw bytes, so structures containing
 * pointers are copied shallowly.
 */
typedef struct {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Stack;

/*
 * Initializes an empty stack for elements of the given size.
 * Returns 0 on success, -1 on error.
 * Does not allocate memory for elements.
 */
int stack_init(Stack *s, size_t element_size);

/*
 * Frees the stack's allocated memory and resets its fields.
 * Does nothing if s is NULL.
 */
void stack_destroy(Stack *s);

/*
 * Pushes a copy of an element onto the top of the stack.
 * Returns 0 on success, -1 on error.
 */
int stack_push(Stack *s, const void *element);

/*
 * Copies the top element into value and removes it.
 * Returns 0 on success, -1 if the stack is empty or an argument is invalid.
 */
int stack_pop(Stack *s, void *value);

/*
 * Copies the top element into value without removing it.
 * Returns 0 on success, -1 if the stack is empty or an argument is invalid.
 */
int stack_peek(const Stack *s, void *value);

/*
 * Returns the number of elements in the stack.
 * Returns 0 if s is NULL.
 */
size_t stack_size(const Stack *s);

/*
 * Returns true if the stack is empty or s is NULL.
 */
bool stack_is_empty(const Stack *s);

/*
 * Removes all elements without releasing allocated memory.
 * Does nothing if s is NULL.
 */
void stack_clear(Stack *s);

#endif
