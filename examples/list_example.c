#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>

static void print_list(const List *list) {
    printf("Size: %zu\n", list_size(list));
    printf("Elements: ");

    for (size_t i = 0; i < list_size(list); i++) {
        int value;

        if (list_get(list, i, &value) != 0) {
            fprintf(stderr, "Error: list_get failed\n");
            return;
        }

        printf("%d ", value);
    }

    puts("NULL");
}

int main(void) {
    List list;

    if (list_init(&list) != 0) {
        fprintf(stderr, "Error: list initialization failed\n");
        return EXIT_FAILURE;
    }

    puts("=== Push elements ===");

    if (list_push_back(&list, 10) != 0 || list_push_back(&list, 20) != 0 ||
        list_push_back(&list, 30) != 0) {
        fprintf(stderr, "Error: failed to append an element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_list(&list);

    puts("\n=== Push front ===");

    if (list_push_front(&list, 5) != 0) {
        fprintf(stderr, "Error: list_push_front failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_list(&list);

    puts("\n=== Insert element ===");

    if (list_insert(&list, 2, 15) != 0) {
        fprintf(stderr, "Error: list_insert failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_list(&list);

    puts("\n=== Get element ===");

    int value;

    if (list_get(&list, 2, &value) != 0) {
        fprintf(stderr, "Error: list_get failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    printf("Element at index 2: %d\n", value);

    puts("\n=== Set element ===");

    if (list_set(&list, 2, 99) != 0) {
        fprintf(stderr, "Error: list_set failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_list(&list);

    puts("\n=== Remove element ===");

    if (list_remove(&list, 2, &value) != 0) {
        fprintf(stderr, "Error: list_remove failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    printf("Removed element: %d\n", value);
    print_list(&list);

    puts("\n=== Pop front and back ===");

    if (list_pop_front(&list, &value) != 0) {
        fprintf(stderr, "Error: list_pop_front failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    printf("Popped front: %d\n", value);

    if (list_pop_back(&list, &value) != 0) {
        fprintf(stderr, "Error: list_pop_back failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    printf("Popped back: %d\n", value);
    print_list(&list);

    puts("\n=== Clear ===");

    if (list_clear(&list) != 0) {
        fprintf(stderr, "Error: list_clear failed\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_list(&list);
    printf("Is empty: %s\n", list_is_empty(&list) ? "yes" : "no");

    list_destroy(&list);
    return EXIT_SUCCESS;
}
