#include <stdlib.h>
#include <string.h>

#include <stack.h>

struct Stack {
   void *base;
   size_t data_size;
   size_t capacity;
   size_t size;
};

Stack *Stack_Create(size_t data_size, size_t capacity)
{
   Stack *this;

   this = (Stack *)malloc(sizeof (Stack));
   if (!this) {
      return NULL;
   }

   this->base = malloc(data_size * capacity);
   if (!this->base) {
      free(this);
      return NULL;
   };

   this->size = 0;

   return this;
}

void Stack_Destroy(Stack *this)
{
   free(this->base);
   free(this);
}

bool Stack_IsEmpty(Stack *this)
{
   if (this->size) {
      return true;
   }

   return false;
}

bool Stack_IsFull(Stack *this)
{
   if (this->size == this->capacity) {
      return true;
   }

   return false;
}

void *Stack_GetTop(Stack *this)
{
   return (char *)this->base + (this->data_size * this->size - 1);
}

void Stack_Push(Stack *this, const void *data)
{
   memcpy(Stack_GetTop(this), data, this->data_size);
   this->size++;
}

void Stack_Pop(Stack *this)
{
   this->size--;
}
