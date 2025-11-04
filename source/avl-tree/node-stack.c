#include <stdlib.h>
#include <string.h>

#include <node-stack.h>

AvlTreeNodeStack AvlTreeNodeStack_Create(DS_Size capacity)
{
     AvlTreeNodeStack stack;

     stack = (AvlTreeNodeStack)malloc(sizeof (struct AvlTreeNodeStack));
     if (!stack) {
          return NULL;
     }

     stack->base = (AvlTreeNode *)malloc(sizeof (struct AvlTreeNode) * capacity);
     if (!stack->base) {
          free(stack);
          return NULL;
     }

     stack->capacity = capacity;
     stack->size = 0;

     return stack;
}

DS_Void AvlTreeNodeStack_Destroy(AvlTreeNodeStack stack)
{
     free(stack->base);
     free(stack);
}

DS_Bool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack this)
{
     if (this->size == 0) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Void AvlTreeNodeStack_Push(AvlTreeNodeStack this, AvlTreeNode node)
{
     this->base[this->size] = node;
     this->size++;
}

DS_Void AvlTreeNodeStack_Pop(AvlTreeNodeStack this)
{
     this->size--;
}