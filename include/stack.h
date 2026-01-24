#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stddef.h>

typedef struct Stack Stack;

typedef enum {
   STACK_BOOL_FALSE = 0,
   STACK_BOOL_TRUE = 1
} StackBool;

__attribute__((visibility("default")))
Stack *Stack_Create(size_t data_size, size_t size);

__attribute__((visibility("default")))
void Stack_Destroy(Stack *this);

__attribute__((visibility("default")))
StackBool Stack_IsEmpty(Stack *this);

__attribute__((visibility("default")))
StackBool Stack_IsFull(Stack *this);

__attribute__((visibility("default")))
void *Stack_GetTop(Stack *this);

__attribute__((visibility("default")))
void Stack_Push(Stack *this, const void *data);

__attribute__((visibility("default")))
void Stack_Pop(Stack *this);

#endif
