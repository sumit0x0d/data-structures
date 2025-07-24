#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stack Stack;

Stack *Stack_Create(size_t dSize, size_t capacity);
void Stack_Destroy(Stack *stack);

bool Stack_IsEmpty(Stack *stack);
bool Stack_IsFull(Stack *stack);

void *Stack_GetTop(Stack *stack);

void Stack_Push(Stack *stack, const void *data);
void Stack_Pop(Stack *stack);

#endif
