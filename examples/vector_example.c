
#include "vector.h"
#include <stdio.h>

int main(void) {
    Vector v;

    if (vector_init(&v) != 0) {
        printf("Failed to initialize vector.\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        if (vector_push(&v, i * 10) != 0) {
            printf("Failed to push element.\n");
            vector_destroy(&v);
            return 1;
        }
    }

    printf("Size: %zu\n", v.size);
    printf("Capacity: %zu\n", v.capacity);

    printf("Elements: ");
    for (size_t i = 0; i < v.size; i++) {
        int value;

        if (vector_get(&v, i, &value) != 0) {
            printf("Failed to get element.\n");
            vector_destroy(&v);
            return 1;
        }

        printf("%d ", value);
    }
    printf("\n");

    int removed_value;

    if (vector_pop(&v, &removed_value) != 0) {
        printf("Failed to pop element.\n");
        vector_destroy(&v);
        return 1;
    }

    printf("Popped element: %d\n", removed_value);
    printf("Size after pop: %zu\n", v.size);

    vector_clear(&v);
    printf("Size after clear: %zu\n", v.size);

    vector_destroy(&v);

    return 0;
}
