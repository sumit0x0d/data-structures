#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <stack.h>

struct Stack {
     Array array;
     DS_Size size;
};

Stack Stack_Create(DS_Size data_size, DS_Size size)
{
     Stack self;

     self = (Stack)malloc(sizeof (struct Stack));
     if (!self) {
          return NULL;
     }

     self->array = Array_Create(data_size, size);
     if (!self->array) {
          free(self);
          return NULL;
     }

     self->size = 0;

     return self;
}

DS_Void Stack_Destroy(Stack self)
{
     Array_Destroy(self->array);
     free(self);
}

DS_Bool Stack_IsEmpty(Stack self)
{
     if (self->size) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Bool Stack_IsFull(Stack self)
{
     if (self->size == Array_GetSize(self->array)) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Generic Stack_GetTop(Stack self)
{
     return Array_GetData(self->array, self->size - 1);
}

DS_Void Stack_Push(Stack self, const DS_Generic data)
{
     Array_SetData(self->array, self->size, data);
     self->size++;
}

DS_Void Stack_Pop(Stack self)
{
     self->size--;
}
