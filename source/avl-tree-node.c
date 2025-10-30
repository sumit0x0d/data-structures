#include <stdlib.h>
#include <string.h>

#include "avl-tree-node.h"

AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
     AvlTreeNode this;

     this = (AvlTreeNode)malloc(sizeof (struct AvlTreeNode));
     if (!this) {
          return NULL;
     }
     
     this->data = malloc(data_size);
     if (!this->data){
          free(this);
          return NULL;
     }
     
     memcpy(this->data, data, data_size);
     this->left = NULL;
     this->right = NULL;
     this->balance_factor = 0;
     
     return this;
}

DS_Void AvlTreeNode_Destroy(AvlTreeNode this)
{
     free(this->data);
     free(this);
}

DS_Size AvlTreeNode_GetHeight(AvlTreeNode this, CircularBuffer circular_buffer)
{
     DS_Size height;
     
     height = 0;
     CircularBuffer_PushBack(circular_buffer, this);
     
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          this = CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (this->left) {
               CircularBuffer_PushBack(circular_buffer, this->left);
          }
          if (this->right) {
               CircularBuffer_PushBack(circular_buffer, this->right);
          }
          height++;
     }

     return height;
}

DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode this, CircularBuffer circular_buffer)
{
     DS_Size left_height;
     DS_Size right_height;
     
     if (this->left) {
          left_height = AvlTreeNode_GetHeight(this->left, circular_buffer);
     } else {
          left_height = 0;
     }
     
     if (this->right) {
          right_height = AvlTreeNode_GetHeight(this->right, circular_buffer);
     } else {
          right_height = 0;
     }

     this->balance_factor = (int)(left_height - right_height);
}

AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode this)
{
     AvlTreeNode left;
     AvlTreeNode previous;

     left = this->left;
     previous = this;
     free(this->data);
     this = left;

     while (this->right) {
          this = this->right;
     }
     
     previous->data = this->data;
     left = this->left;
     previous = this->parent;
     previous->right = left;
     
     if (left) {
          left->parent = previous;
     }
     
     free(this);
     
     return previous;
}

AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode this)
{
     AvlTreeNode right;
     AvlTreeNode previous;

     right = this->right;
     previous = this;
     free(this->data);
     this = right;

     while (this->left) {
          this = this->left;
     }

     previous->data = this->data;
     right = this->right;
     previous = this->parent;
     previous->left = right;

     if (right) {
          right->parent = previous;
     }

     free(this);

     return previous;
}