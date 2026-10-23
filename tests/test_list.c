#include "list.h"

#include <assert.h>
#include <stdio.h>

static void check_list(const List *l) {
    assert(l != NULL);

    size_t count = 0;
    const ListNode *current = l->head;
    const ListNode *last = NULL;

    while (current != NULL) {
        count++;
        last = current;
        current = current->next;
    }

    assert(count == l->size);
    assert(last == l->tail);

    if (l->size == 0) {
        assert(l->head == NULL);
        assert(l->tail == NULL);
    } else {
        assert(l->head != NULL);
        assert(l->tail != NULL);
        assert(l->tail->next == NULL);
    }
}

static void test_init_and_empty(void) {
    List l;

    assert(list_size(NULL) == 0);
    assert(list_is_empty(NULL));
    assert(list_init(NULL) == -1);
    assert(list_init(&l) == 0);
    assert(list_is_empty(&l));
    assert(list_size(&l) == 0);

    check_list(&l);
    list_destroy(&l);
}

static void test_push(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_push_front(&l, 5) == 0);
    check_list(&l);
    assert(l.head == l.tail);

    assert(list_push_back(&l, 10) == 0);
    check_list(&l);

    assert(list_push_front(&l, 1) == 0);
    check_list(&l);

    assert(list_size(&l) == 3);
    assert(list_get(&l, 0, &value) == 0 && value == 1);
    assert(list_get(&l, 1, &value) == 0 && value == 5);
    assert(list_get(&l, 2, &value) == 0 && value == 10);

    assert(list_push_front(NULL, 1) == -1);
    assert(list_push_back(NULL, 1) == -1);

    list_destroy(&l);
}

static void test_pop(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_pop_front(&l, &value) == -1);
    assert(list_pop_back(&l, &value) == -1);

    assert(list_push_back(&l, 10) == 0);
    check_list(&l);

    assert(list_pop_back(&l, &value) == 0);
    assert(value == 10);
    check_list(&l);

    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);
    check_list(&l);

    assert(list_pop_front(&l, &value) == 0);
    assert(value == 10);
    check_list(&l);

    assert(list_pop_back(&l, &value) == 0);
    assert(value == 30);
    check_list(&l);

    assert(list_pop_back(&l, &value) == 0);
    assert(value == 20);
    check_list(&l);

    assert(list_is_empty(&l));
    assert(list_size(&l) == 0);

    assert(list_pop_front(&l, &value) == -1);
    assert(list_pop_back(&l, &value) == -1);

    list_destroy(&l);
}

static void test_get_and_set(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);

    assert(list_get(&l, 0, &value) == 0 && value == 10);
    assert(list_get(&l, 1, &value) == 0 && value == 20);
    assert(list_get(&l, 2, &value) == 0 && value == 30);

    assert(list_set(&l, 1, 99) == 0);
    assert(list_get(&l, 1, &value) == 0 && value == 99);

    assert(list_get(&l, 3, &value) == -1);
    assert(list_get(&l, 0, NULL) == -1);
    assert(list_set(&l, 3, 100) == -1);
    assert(list_set(NULL, 0, 100) == -1);

    assert(list_size(&l) == 3);
    check_list(&l);

    list_destroy(&l);
}

static void test_insert(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_insert(&l, 0, 20) == 0);
    check_list(&l);
    assert(l.head == l.tail);

    assert(list_insert(&l, 0, 10) == 0);
    check_list(&l);

    assert(list_insert(&l, 1, 15) == 0);
    check_list(&l);

    assert(list_insert(&l, list_size(&l), 30) == 0);
    check_list(&l);

    assert(list_size(&l) == 4);
    assert(list_get(&l, 0, &value) == 0 && value == 10);
    assert(list_get(&l, 1, &value) == 0 && value == 15);
    assert(list_get(&l, 2, &value) == 0 && value == 20);
    assert(list_get(&l, 3, &value) == 0 && value == 30);

    assert(list_insert(&l, 5, 50) == -1);
    assert(list_insert(NULL, 0, 1) == -1);

    list_destroy(&l);
}

static void test_remove(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_remove(&l, 0, &value) == -1);
    assert(list_remove(&l, 0, NULL) == -1);

    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);
    assert(list_push_back(&l, 40) == 0);
    check_list(&l);

    assert(list_remove(&l, 1, &value) == 0);
    assert(value == 20);
    check_list(&l);

    assert(list_remove(&l, list_size(&l) - 1, &value) == 0);
    assert(value == 40);
    check_list(&l);

    assert(list_remove(&l, 0, &value) == 0);
    assert(value == 10);
    check_list(&l);

    assert(list_remove(&l, 0, &value) == 0);
    assert(value == 30);
    check_list(&l);

    assert(list_is_empty(&l));
    assert(list_remove(&l, 0, &value) == -1);

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
    check_list(&l);

    assert(list_get(&l, 1, &value) == -1);
    assert(list_set(&l, 1, 20) == -1);
    assert(list_remove(&l, 1, &value) == -1);
    assert(list_insert(&l, 2, 20) == -1);

    assert(list_insert(&l, 1, 20) == 0);
    check_list(&l);

    assert(list_size(&l) == 2);

    list_destroy(&l);
}

static void test_clear(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_clear(&l) == 0);
    check_list(&l);

    assert(list_push_back(&l, 10) == 0);
    assert(list_push_back(&l, 20) == 0);
    assert(list_push_back(&l, 30) == 0);
    check_list(&l);

    assert(list_clear(&l) == 0);
    check_list(&l);

    assert(list_clear(&l) == 0);
    check_list(&l);

    assert(list_push_back(&l, 42) == 0);
    check_list(&l);

    assert(list_get(&l, 0, &value) == 0 && value == 42);

    list_destroy(&l);
}

static void test_null_arguments(void) {
    List l;
    int value;

    assert(list_init(&l) == 0);

    assert(list_init(NULL) == -1);
    assert(list_clear(NULL) == -1);

    assert(list_push_front(NULL, 1) == -1);
    assert(list_push_back(NULL, 1) == -1);

    assert(list_pop_front(&l, NULL) == -1);
    assert(list_pop_back(&l, NULL) == -1);

    assert(list_get(&l, 0, NULL) == -1);
    assert(list_remove(&l, 0, NULL) == -1);

    assert(list_set(NULL, 0, 1) == -1);
    assert(list_insert(NULL, 0, 1) == -1);

    assert(list_get(NULL, 0, &value) == -1);
    assert(list_remove(NULL, 0, &value) == -1);

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
    test_null_arguments();

    puts("All list tests passed.");
    return 0;
}
