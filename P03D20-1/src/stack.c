#include "stack.h"

#include <stdlib.h>
#include <string.h>

Stack* create_stack(int capacity, int element_size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->element_size = element_size;
    stack->data = malloc(capacity * element_size);
    return stack;
}

void push(Stack* stack, const void* value) {
    if (stack->top == stack->capacity - 1) return;
    stack->top++;
    memcpy((char*)stack->data + stack->top * stack->element_size, value, stack->element_size);
}

void* pop(Stack* stack) {
    if (stack->top == -1) return NULL;
    void* value = malloc(stack->element_size);
    memcpy(value, (char*)stack->data + stack->top * stack->element_size, stack->element_size);
    stack->top--;
    return value;
}

void* peek(Stack* stack) {
    if (stack->top == -1) return NULL;
    return (char*)stack->data + stack->top * stack->element_size;
}

void destroy_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}