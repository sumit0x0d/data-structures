#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <data-structures.h>

typedef struct Stack * Stack;

DATA_STRUCTURES_API
Stack Stack_Create(DS_Size data_size, DS_Size size);

DATA_STRUCTURES_API
DS_Void Stack_Destroy(Stack self);

DATA_STRUCTURES_API
DS_Bool Stack_IsEmpty(Stack self);

DATA_STRUCTURES_API
DS_Bool Stack_IsFull(Stack self);

DATA_STRUCTURES_API
DS_Generic Stack_GetTop(Stack self);

DATA_STRUCTURES_API
DS_Void Stack_Push(Stack self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void Stack_Pop(Stack self);

#endif