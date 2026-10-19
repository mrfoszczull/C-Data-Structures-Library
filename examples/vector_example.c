#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

static void print_vector(const Vector *v) {
    printf("Size: %zu\n", v->size);
    printf("Capacity: %zu\n", v->capacity);
    printf("Elements: ");

    for (size_t i = 0; i < v->size; i++) {
        int value;

        if (vector_get(v, i, &value) != 0) {
            fprintf(stderr, "Error: vector_get failed\n");
            return;
        }

        printf("%d ", value);
    }

    putchar('\n');
}

int main(void) {
    Vector v;

    if (vector_init(&v) != 0) {
        fprintf(stderr, "Error: vector initialization failed\n");
        return EXIT_FAILURE;
    }

    puts("=== Push elements ===");

    for (int i = 10; i <= 50; i += 10) {
        if (vector_push(&v, i) != 0) {
            fprintf(stderr, "Error: vector_push failed\n");
            vector_destroy(&v);
            return EXIT_FAILURE;
        }
    }

    print_vector(&v);

    puts("\n=== Set element ===");

    if (vector_set(&v, 2, 35) != 0) {
        fprintf(stderr, "Error: vector_set failed\n");
        vector_destroy(&v);
        return EXIT_FAILURE;
    }

    print_vector(&v);

    puts("\n=== Get element ===");

    int value;

    if (vector_get(&v, 2, &value) != 0) {
        fprintf(stderr, "Error: vector_get failed\n");
        vector_destroy(&v);
        return EXIT_FAILURE;
    }

    printf("Element at index 2: %d\n", value);

    puts("\n=== Pop element ===");

    if (vector_pop(&v, &value) != 0) {
        fprintf(stderr, "Error: vector_pop failed\n");
        vector_destroy(&v);
        return EXIT_FAILURE;
    }

    printf("Popped element: %d\n", value);
    print_vector(&v);

    puts("\n=== Resize to 6 ===");

    if (vector_resize(&v, 6) != 0) {
        fprintf(stderr, "Error: vector_resize failed\n");
        vector_destroy(&v);
        return EXIT_FAILURE;
    }

    print_vector(&v);

    puts("\n=== Clear ===");

    vector_clear(&v);
    print_vector(&v);

    vector_destroy(&v);
    return EXIT_SUCCESS;
}
