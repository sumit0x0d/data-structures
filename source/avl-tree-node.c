#include <stdlib.h>
#include <string.h>

#include "avl-tree-node.h"

AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
     AvlTreeNode self;

     self = (AvlTreeNode)malloc(sizeof (struct AvlTreeNode));
     if (!self) {
          return NULL;
     }
     
     self->data = malloc(data_size);
     if (!self->data){
          free(self);
          return NULL;
     }
     
     memcpy(self->data, data, data_size);
     self->left = NULL;
     self->right = NULL;
     self->balance_factor = 0;
     
     return self;
}

DS_Void AvlTreeNode_Destroy(AvlTreeNode self)
{
     free(self->data);
     free(self);
}

DS_Size AvlTreeNode_GetHeight(AvlTreeNode self, CircularBuffer circular_buffer)
{
     DS_Size height;
     
     height = 0;
     CircularBuffer_PushBack(circular_buffer, self);
     
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          self = CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (self->left) {
               CircularBuffer_PushBack(circular_buffer, self->left);
          }
          if (self->right) {
               CircularBuffer_PushBack(circular_buffer, self->right);
          }
          height++;
     }

     return height;
}

DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode self, CircularBuffer circular_buffer)
{
     DS_Size left_height;
     DS_Size right_height;
     
     if (self->left) {
          left_height = AvlTreeNode_GetHeight(self->left, circular_buffer);
     } else {
          left_height = 0;
     }
     
     if (self->right) {
          right_height = AvlTreeNode_GetHeight(self->right, circular_buffer);
     } else {
          right_height = 0;
     }

     self->balance_factor = (int)(left_height - right_height);
}

AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode self)
{
     AvlTreeNode left;
     AvlTreeNode previous;

     left = self->left;
     previous = self;
     free(self->data);
     self = left;

     while (self->right) {
          self = self->right;
     }
     
     previous->data = self->data;
     left = self->left;
     previous = self->parent;
     previous->right = left;
     
     if (left) {
          left->parent = previous;
     }
     
     free(self);
     
     return previous;
}

AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode self)
{
     AvlTreeNode right;
     AvlTreeNode previous;

     right = self->right;
     previous = self;
     free(self->data);
     self = right;

     while (self->left) {
          self = self->left;
     }

     previous->data = self->data;
     right = self->right;
     previous = self->parent;
     previous->left = right;

     if (right) {
          right->parent = previous;
     }

     free(self);

     return previous;
}