#include <assert.h>
#include <stdlib.h>

#include <stack.h>

struct Stack {
     DS_Generic base;
     DS_Size data_size;
     DS_Size capacity;
     DS_Size size;
};

Stack Stack_Create(DS_Size data_size, DS_Size capacity)
{
     Stack this;

     this = (Stack)malloc(sizeof (struct Stack));
     if (!this) {
          return NULL;
     }

     this->base = (DS_Generic)malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->size = 0;

     return this;
}

DS_Void Stack_Destroy(Stack this)
{
     free(this->base);
     free(this);
}

DS_Bool Stack_IsEmpty(Stack this)
{
     if (this->size) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Bool Stack_IsFull(Stack this)
{
     if (this->size == this->capacity) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Generic Stack_GetTop(Stack this)
{
     return (DS_Int8 *)this->base + (this->data_size * this->size - 1);
}

DS_Void Stack_Push(Stack this, const DS_Generic data)
{
     memcpy(Stack_GetTop(this), data, this->data_size);
     this->size++;
}

DS_Void Stack_Pop(Stack this)
{
     this->size--;
}
