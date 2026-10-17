#include "../include/vector.h"
#include <assert.h>
#include <stdio.h>

static void test_init_and_empty(void) {
    Vector v;

    assert(vector_init(&v) == 0);
    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);

    vector_destroy(&v);
}

static void test_push_and_get(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);

    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);
    assert(vector_push(&v, 30) == 0);

    assert(v.size == 3);

    assert(vector_get(&v, 0, &value) == 0 && value == 10);
    assert(vector_get(&v, 1, &value) == 0 && value == 20);
    assert(vector_get(&v, 2, &value) == 0 && value == 30);

    vector_destroy(&v);
}

static void test_set(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);
    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);

    assert(vector_set(&v, 1, 99) == 0);
    assert(vector_get(&v, 1, &value) == 0 && value == 99);
    assert(v.size == 2);

    vector_destroy(&v);
}

static void test_pop(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);
    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);

    assert(vector_pop(&v, &value) == 0 && value == 20);
    assert(v.size == 1);

    assert(vector_pop(&v, &value) == 0 && value == 10);
    assert(v.size == 0);

    assert(vector_pop(&v, &value) == -1);

    vector_destroy(&v);
}

static void test_reserve(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);
    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);

    size_t old_capacity = v.capacity;

    assert(vector_reserve(&v, old_capacity + 10) == 0);
    assert(v.capacity >= old_capacity + 10);
    assert(v.size == 2);

    assert(vector_get(&v, 0, &value) == 0 && value == 10);
    assert(vector_get(&v, 1, &value) == 0 && value == 20);

    vector_destroy(&v);
}

static void test_resize(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);
    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);

    assert(vector_resize(&v, 5) == 0);
    assert(v.size == 5);

    assert(vector_get(&v, 0, &value) == 0 && value == 10);
    assert(vector_get(&v, 1, &value) == 0 && value == 20);
    assert(vector_get(&v, 2, &value) == 0 && value == 0);
    assert(vector_get(&v, 3, &value) == 0 && value == 0);
    assert(vector_get(&v, 4, &value) == 0 && value == 0);

    assert(vector_resize(&v, 2) == 0);
    assert(v.size == 2);
    assert(vector_get(&v, 0, &value) == 0 && value == 10);
    assert(vector_get(&v, 1, &value) == 0 && value == 20);

    assert(vector_resize(&v, 0) == 0);
    assert(v.size == 0);

    vector_destroy(&v);
}

static void test_clear(void) {
    Vector v;

    assert(vector_init(&v) == 0);
    assert(vector_push(&v, 10) == 0);
    assert(vector_push(&v, 20) == 0);

    size_t old_capacity = v.capacity;

    vector_clear(&v);

    assert(v.size == 0);
    assert(v.capacity == old_capacity);

    assert(vector_push(&v, 42) == 0);
    assert(v.size == 1);

    int value;
    assert(vector_get(&v, 0, &value) == 0 && value == 42);

    vector_destroy(&v);
}

static void test_invalid_operations(void) {
    Vector v;
    int value;

    assert(vector_init(&v) == 0);

    assert(vector_get(&v, 0, &value) == -1);
    assert(vector_set(&v, 0, 10) == -1);
    assert(vector_pop(&v, &value) == -1);

    assert(vector_push(&v, 10) == 0);

    assert(vector_get(&v, 1, &value) == -1);
    assert(vector_set(&v, 1, 20) == -1);

    vector_destroy(&v);
}

int main(void) {
    test_init_and_empty();
    test_push_and_get();
    test_set();
    test_pop();
    test_reserve();
    test_resize();
    test_clear();
    test_invalid_operations();

    puts("All vector tests passed.");
    return 0;
}
