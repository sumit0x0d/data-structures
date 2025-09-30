#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <data-structures.h>

typedef struct stack * Stack;

DS_API
Stack Stack_Create(DS_Size data_size, DS_Size size);

DS_API
DS_Void Stack_Destroy(Stack stack);

DS_API
DS_Bool Stack_IsEmpty(Stack stack);

DS_API
DS_Bool Stack_IsFull(Stack stack);

DS_API
DS_Generic Stack_GetTop(Stack stack);

DS_API
DS_Void Stack_Push(Stack stack, const DS_Generic data);

DS_API
DS_Void Stack_Pop(Stack stack);

#endif
