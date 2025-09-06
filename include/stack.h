#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <data-structures.h>

typedef struct stack Stack;

DS_PUBLIC_API
Stack *DS_Stack_Create(DS_Size sData, DS_Size capacity);

DS_PUBLIC_API
void DS_Stack_Destroy(Stack *stack);

DS_PUBLIC_API
DS_Bool DS_Stack_IsEmpty(Stack *stack);

DS_PUBLIC_API
DS_Bool DS_Stack_IsFull(Stack *stack);

DS_PUBLIC_API
DS_Data DS_Stack_GetTop(Stack *stack);

DS_PUBLIC_API
void DS_Stack_Push(Stack *stack, const DS_Data data);

DS_PUBLIC_API
void DS_Stack_Pop(Stack *stack);

#endif
