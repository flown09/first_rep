#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    void* data;
    int top;
    int capacity;
    int element_size;
} Stack;

Stack* create_stack(int capacity, int element_size);
void push(Stack* stack, const void* value);
void* pop(Stack* stack);
void* peek(Stack* stack);
void destroy_stack(Stack* stack);

#endif  // STACK_H