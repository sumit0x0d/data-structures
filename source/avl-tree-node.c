#include <stdlib.h>
#include <string.h>

#include "avl-tree-node.h"

AvlTreeNode AvlTreeNode_Create(
     const DS_Generic data,
     DS_Size          data_size
) {
     AvlTreeNode node;

     node = (AvlTreeNode)malloc(sizeof (struct AvlTreeNode));
     if (!node) {
          return NULL;
     }
     
     node->data = malloc(data_size);
     if (!node->data){
          free(node);
          return NULL;
     }
     
     memcpy(node->data, data, data_size);
     node->left = NULL;
     node->right = NULL;
     node->balance_factor = 0;
     
     return node;
}

DS_Void AvlTreeNode_Destroy(
     AvlTreeNode node
) {
     free(node->data);
     free(node);
}

DS_Size AvlTreeNode_GetHeight(
     AvlTreeNode    node,
     CircularBuffer circular_buffer
) {
     DS_Size height;
     
     height = 0;
     CircularBuffer_PushBack(circular_buffer, node);
     
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          node = CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (node->left) {
               CircularBuffer_PushBack(circular_buffer, node->left);
          }
          if (node->right) {
               CircularBuffer_PushBack(circular_buffer, node->right);
          }
          height++;
     }

     return height;
}

DS_Void AvlTreeNode_UpdateBalanceFactor(
     AvlTreeNode    node,
     CircularBuffer circular_buffer
) {
     DS_Size left_height;
     DS_Size right_height;
     
     if (node->left) {
          left_height = AvlTreeNode_GetHeight(node->left, circular_buffer);
     } else {
          left_height = 0;
     }
     
     if (node->right) {
          right_height = AvlTreeNode_GetHeight(node->right, circular_buffer);
     } else {
          right_height = 0;
     }

     node->balance_factor = (int)(left_height - right_height);
}

AvlTreeNode AvlTreeNode_GetPredecessor(
     AvlTreeNode node
) {
     AvlTreeNode left;
     AvlTreeNode previous;

     left = node->left;
     previous = node;
     free(node->data);
     node = left;

     while (node->right) {
          node = node->right;
     }
     
     previous->data = node->data;
     left = node->left;
     previous = node->parent;
     previous->right = left;
     
     if (left) {
          left->parent = previous;
     }
     
     free(node);
     
     return previous;
}

AvlTreeNode AvlTreeNode_GetSuccessor(
     AvlTreeNode node
) {
     AvlTreeNode right;
     AvlTreeNode previous;

     right = node->right;
     previous = node;
     free(node->data);
     node = right;

     while (node->left) {
          node = node->left;
     }

     previous->data = node->data;
     right = node->right;
     previous = node->parent;
     previous->left = right;

     if (right) {
          right->parent = previous;
     }

     free(node);

     return previous;
}