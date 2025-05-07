#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    int capacity; // current capacity of the stack
    int top;      // index of the top element, -1 when empty
} Stack;

// Create a new stack with an initial capacity.
Stack *create_stack(int capacity);

// Push a value onto the stack (grows capacity if needed).
void push(Stack *stack, int value);

// Pop a value from the stack.
int pop(Stack *stack);

// Peek at the top value without removing it.
int peek(Stack *stack);

// Free the stack memory.
void free_stack(Stack *stack);

#endif // STACK_H