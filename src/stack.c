#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    int capacity; // current capacity of the stack
    int top;      // index of the top element, -1 when empty
} Stack;

// Create a new stack with an initial capacity
Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    stack->data = malloc(capacity * sizeof(int));
    if (!stack->data) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

// Push a value onto the stack, growing it if needed
void push(Stack *stack, int value) {
    if (stack->top == stack->capacity - 1) { // stack full, grow capacity
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(int));
        if (!stack->data) {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }
    }
    stack->data[++stack->top] = value;
}

// Pop a value from the stack
int pop(Stack *stack) {
    if (stack->top == -1) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Peek at the top value without removing it
int peek(Stack *stack) {
    if (stack->top == -1) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Free stack memory
void free_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

#endif