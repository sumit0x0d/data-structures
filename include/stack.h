#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack;

__attribute__((visibility("default")))
Stack *Stack_Create(size_t data_size, size_t size);

__attribute__((visibility("default")))
void Stack_Destroy(Stack *this);

__attribute__((visibility("default")))
bool Stack_IsEmpty(Stack *this);

__attribute__((visibility("default")))
bool Stack_IsFull(Stack *this);

__attribute__((visibility("default")))
void *Stack_GetTop(Stack *this);

__attribute__((visibility("default")))
void Stack_Push(Stack *this, const void *data);

__attribute__((visibility("default")))
void Stack_Pop(Stack *this);

#endif