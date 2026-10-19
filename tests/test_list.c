#include "list.h"
#include <assert.h>
#include <stdio.h>

static void test_init_and_empty(void) {
    List l;

    assert(list_size(NULL) == 0);
    assert(list_is_empty(NULL));

    assert(list_init(&l) == 0);
    assert(list_is_empty(&l));
    assert(list_size(&l) == 0);

    list_destroy(&l);
}

static void test_push(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_front(&l, 5) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_size(&l) == 2);
    assert(list_get(&l, 0, &value) == 0 && value == 5);
    assert(list_get(&l, 1, &value) == 0 && value == 10);

    list_destroy(&l);
}

static void test_pop(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_pop_front(&l, &value) == 0 && value == 10);
    assert(list_size(&l) == 1);
    assert(list_pop_back(&l, &value) == 0 && value == 20);
    assert(list_is_empty(&l));
    assert(list_size(&l) == 0);

    list_destroy(&l);
}

static void test_get_and_set(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);

    assert(list_get(&l, 1, &value) == 0 && value == 20);
    assert(list_set(&l, 1, 99) == 0);
    assert(list_get(&l, 1, &value) == 0 && value == 99);

    assert(list_size(&l) == 3);

    list_destroy(&l);
}

static void test_insert(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 30) == 0);

    assert(list_insert(&l, 1, 20) == 0);
    assert(list_size(&l) == 3);

    assert(list_get(&l, 0, &value) == 0 && value == 10);
    assert(list_get(&l, 1, &value) == 0 && value == 20);
    assert(list_get(&l, 2, &value) == 0 && value == 30);

    assert(list_insert(&l, 0, 5) == 0);
    assert(list_get(&l, 0, &value) == 0 && value == 5);

    assert(list_insert(&l, list_size(&l), 40) == 0);
    assert(list_get(&l, list_size(&l) - 1, &value) == 0 && value == 40);

    assert(list_size(&l) == 5);

    list_destroy(&l);
}

static void test_remove(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);

    assert(list_remove(&l, 1, &value) == 0 && value == 20);
    assert(list_size(&l) == 2);
    assert(list_get(&l, 0, &value) == 0 && value == 10);
    assert(list_get(&l, 1, &value) == 0 && value == 30);

    assert(list_remove(&l, 0, &value) == 0 && value == 10);
    assert(list_size(&l) == 1);

    assert(list_remove(&l, 0, &value) == 0 && value == 30);
    assert(list_is_empty(&l));

    list_destroy(&l);
}

static void test_invalid_operations(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_pop_front(&l, &value) == -1);
    assert(list_pop_back(&l, &value) == -1);
    assert(list_get(&l, 0, &value) == -1);
    assert(list_set(&l, 0, 10) == -1);
    assert(list_remove(&l, 0, &value) == -1);
    assert(list_insert(&l, 1, 10) == -1);

    assert(list_push_back(&l, 10) == 0);

    assert(list_get(&l, 1, &value) == -1);
    assert(list_set(&l, 1, 20) == -1);
    assert(list_remove(&l, 1, &value) == -1);

    assert(list_insert(&l, 1, 20) == 0);
    assert(list_size(&l) == 2);

    list_destroy(&l);
}

static void test_clear(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);
    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);

    assert(list_clear(&l) == 0);
    assert(list_is_empty(&l));
    assert(list_size(&l) == 0);

    assert(list_push_back(&l, 42) == 0);
    assert(list_get(&l, 0, &value) == 0 && value == 42);

    list_destroy(&l);
}

int main(void) {
    test_init_and_empty();
    test_push();
    test_pop();
    test_get_and_set();
    test_insert();
    test_remove();
    test_invalid_operations();
    test_clear();

    puts("All list tests passed.");
    return 0;
}
