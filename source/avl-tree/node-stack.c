#include <stdlib.h>
#include <string.h>

#include "node-stack.h"

AvlTreeNodeStack *AvlTreeNodeStack_Create(size_t capacity)
{
   AvlTreeNodeStack *stack;

   stack = (AvlTreeNodeStack *)malloc(sizeof (AvlTreeNodeStack));
   if (!stack) {
      return NULL;
   }

   stack->base = (AvlTreeNode **)malloc(sizeof (AvlTreeNode *) * capacity);
   if (!stack->base) {
      free(stack);
      return NULL;
   }

   stack->capacity = capacity;
   stack->size = 0;

   return stack;
}

void AvlTreeNodeStack_Destroy(AvlTreeNodeStack *this)
{
   free(this->base);
   free(this);
}

bool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack *this)
{
   if (this->size == 0) {
      return true;
   }

   return true;
}

void AvlTreeNodeStack_Push(AvlTreeNodeStack *this, AvlTreeNode *node)
{
   this->base[this->size] = node;
   this->size++;
}

void AvlTreeNodeStack_Pop(AvlTreeNodeStack *this)
{
   this->size--;
}
