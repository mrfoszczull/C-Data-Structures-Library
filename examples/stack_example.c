
#include "../include/stack.h"

#include <stdio.h>

int main(void) {
    Stack stack;

    if (stack_init(&stack, sizeof(int)) != 0) {
        fprintf(stderr, "Failed to initialize stack.\n");
        return 1;
    }

    int a = 10;
    int b = 20;
    int c = 30;

    if (stack_push(&stack, &a) != 0 || stack_push(&stack, &b) != 0 ||
        stack_push(&stack, &c) != 0) {
        fprintf(stderr, "Failed to push an element.\n");
        stack_destroy(&stack);
        return 1;
    }

    printf("Stack size: %zu\n", stack_size(&stack));

    int value;

    if (stack_peek(&stack, &value) == 0) {
        printf("Top element: %d\n", value);
    }

    printf("Popping elements:\n");

    while (!stack_is_empty(&stack)) {
        if (stack_pop(&stack, &value) == 0) {
            printf("%d\n", value);
        }
    }

    printf("Stack is empty: %s\n", stack_is_empty(&stack) ? "yes" : "no");

    stack_destroy(&stack);

    return 0;
}
