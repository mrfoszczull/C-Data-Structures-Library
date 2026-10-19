#include "stack.h"
#include <assert.h>
#include <stdio.h>

static void test_init(void) {
    Stack s;
    Stack sc;

    assert(stack_init(&s, sizeof(int)) == 0);
    assert(s.data == NULL);
    assert(s.size == 0);
    assert(s.capacity == 0);
    assert(s.element_size == sizeof(int));

    assert(stack_init(&sc, 0) == -1);
    assert(stack_init(NULL, sizeof(int)) == -1);

    stack_destroy(&s);

    assert(s.data == NULL);
    assert(s.element_size == 0);
    assert(s.size == 0);
    assert(s.capacity == 0);
}

static void test_push(void) {
    Stack s;

    assert(stack_init(&s, sizeof(int)) == 0);

    int value = 10;
    assert(stack_push(&s, &value) == 0);
    assert(s.size == 1);

    value = 20;
    assert(stack_push(&s, &value) == 0);
    assert(s.size == 2);

    value = 30;
    assert(stack_push(&s, &value) == 0);
    assert(s.size == 3);

    assert(s.capacity == 4);

    int *data = (int *)s.data;
    assert(data[0] == 10);
    assert(data[1] == 20);
    assert(data[2] == 30);

    stack_destroy(&s);
}

static void test_pop(void) {
    Stack s;
    assert(stack_init(&s, sizeof(int)) == 0);

    int value = 10;
    assert(stack_push(&s, &value) == 0);

    value = 20;
    assert(stack_push(&s, &value) == 0);

    value = 30;
    assert(stack_push(&s, &value) == 0);

    int result = 0;

    assert(stack_pop(&s, &result) == 0);
    assert(result == 30);
    assert(stack_size(&s) == 2);

    assert(stack_pop(&s, &result) == 0);
    assert(result == 20);
    assert(stack_size(&s) == 1);

    assert(stack_pop(&s, &result) == 0);
    assert(result == 10);
    assert(stack_size(&s) == 0);

    assert(stack_pop(&s, &result) == -1);
    assert(stack_size(&s) == 0);

    stack_destroy(&s);
}

static void test_peek(void) {
    Stack s;
    assert(stack_init(&s, sizeof(int)) == 0);

    int a = 10;
    int b = 20;
    int value = 0;

    assert(stack_peek(&s, &value) == -1);

    assert(stack_push(&s, &a) == 0);
    assert(stack_push(&s, &b) == 0);

    assert(stack_peek(&s, &value) == 0);
    assert(value == 20);
    assert(stack_size(&s) == 2);

    value = 0;
    assert(stack_peek(&s, &value) == 0);
    assert(value == 20);

    assert(stack_pop(&s, &value) == 0);
    assert(value == 20);
    assert(stack_size(&s) == 1);

    stack_destroy(&s);
}

static void test_is_empty(void) {
    Stack s;
    assert(stack_init(&s, sizeof(int)) == 0);

    assert(stack_is_empty(&s) == true);

    int value = 42;
    assert(stack_push(&s, &value) == 0);
    assert(stack_is_empty(&s) == false);

    assert(stack_pop(&s, &value) == 0);
    assert(stack_is_empty(&s) == true);

    assert(stack_is_empty(NULL) == true);

    stack_destroy(&s);
}

static void test_clear(void) {
    Stack s;
    assert(stack_init(&s, sizeof(int)) == 0);

    int a = 10;
    int b = 20;

    assert(stack_push(&s, &a) == 0);
    assert(stack_push(&s, &b) == 0);

    size_t old_capacity = s.capacity;
    assert(stack_size(&s) == 2);

    stack_clear(&s);

    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s) == true);
    assert(s.capacity == old_capacity);

    assert(stack_push(&s, &a) == 0);
    assert(stack_size(&s) == 1);

    int value = 0;
    assert(stack_peek(&s, &value) == 0);
    assert(value == 10);

    stack_clear(&s);

    assert(stack_pop(&s, &value) == -1);

    stack_destroy(&s);
}

int main(void) {
    test_init();
    test_push();
    test_pop();
    test_peek();
    test_is_empty();
    test_clear();

    printf("All stack tests passed\n");

    return 0;
}
