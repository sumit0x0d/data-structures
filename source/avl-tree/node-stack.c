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

AvlTreeNodeStackBool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack *this)
{
   if (this->size == 0) {
      return AVL_TREE_NODE_STACK_BOOL_TRUE;
   }

   return AVL_TREE_NODE_STACK_BOOL_FALSE;
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
