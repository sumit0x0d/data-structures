#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <data-structures.h>

typedef struct stack Stack;

DS_PUBLIC_API
Stack *Stack_Create(DS_Size sData, DS_Size capacity);

DS_PUBLIC_API
void Stack_Destroy(Stack *stack);

DS_PUBLIC_API
DS_Bool Stack_IsEmpty(Stack *stack);

DS_PUBLIC_API
DS_Bool Stack_IsFull(Stack *stack);

DS_PUBLIC_API
DS_Data Stack_GetTop(Stack *stack);

DS_PUBLIC_API
void Stack_Push(Stack *stack, const DS_Data data);

DS_PUBLIC_API
void Stack_Pop(Stack *stack);

#endif
