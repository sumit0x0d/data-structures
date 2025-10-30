#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>
#include <circular-buffer.h>
#include <stack.h>

#include "avl-tree-node.h"

// #include "binary-tree-i.h"

struct AvlTree {
     AvlTreeNode root;
     DS_Size data_size;
     DS_Size size;
     DS_CompareCallback compare_callback;
};

static DS_Void _Rebalance(AvlTree this, AvlTreeNode node, CircularBuffer circular_buffer);
static DS_Void _RotateRight(AvlTree this, AvlTreeNode node);
static DS_Void _RotateLeftRight(AvlTree this, AvlTreeNode node);
static DS_Void _RotateLeft(AvlTree this, AvlTreeNode node);
static DS_Void _RotateRightLeft(AvlTree this, AvlTreeNode node);

AvlTree AvlTree_Create(DS_Size data_size, DS_CompareCallback compare_callback)
{
     AvlTree this;

     this = (AvlTree)malloc(sizeof (struct AvlTree));
     if (!this) {
          return NULL;
     }
     
     this->root = NULL;
     this->data_size = data_size;
     this->size = 0;
     this->compare_callback = compare_callback;
     
     return this;
}

DS_Void AvlTree_Destroy(AvlTree this)
{
     AvlTreeNode node ;
     CircularBuffer circular_buffer;

     node = this->root;
     circular_buffer = CircularBuffer_Create(sizeof (AvlTreeNode), this->size);
     
     free(node->data);
     CircularBuffer_PushBack(circular_buffer, node);
     
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          node = (AvlTreeNode)CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (node->left) {
               free(node->data);
               CircularBuffer_PushBack(circular_buffer, node->left);
          }
          if (node->right) {
               free(node->data);
               CircularBuffer_PushBack(circular_buffer, node->right);
          }
     }
     
     CircularBuffer_Destroy(circular_buffer);
     free(this);
}

DS_Size AvlTree_GetSize(AvlTree this)
{
     return this->size;
}

DS_Size AvlTree_GetDataSize(AvlTree this)
{
     return this->data_size;
}

AvlTreeNode AvlTree_Search(AvlTree this, const DS_Generic data)
{
     AvlTreeNode current;
     DS_Compare compare;

     current = this->root;
     while (current) {
          compare = this->compare_callback.function(data, current->data, this->compare_callback.user_data);
          switch (compare) {
          case DS_COMPARE_LESS:
               current = current->left;
               break;
          case DS_COMPARE_EQUAL:
               return current;
          case DS_COMPARE_GREATER:
               current = current->right;
               break;
          }
     }

     return NULL;
}

DS_Void AvlTree_Insert(AvlTree this, const DS_Generic data)
{
     CircularBuffer circular_buffer;
     AvlTreeNode current;
     AvlTreeNode parent;
     DS_Compare compare;

     if (!this->root) {
          this->root = AvlTreeNode_Create(data, this->data_size);
          this->root->parent = NULL;
          this->size++;
          return;
     }
     
     circular_buffer = CircularBuffer_Create(sizeof (struct AvlTreeNode), (this->size + 2) / 2);
     parent = this->root->parent;
          
     current = this->root;
     while (current) {
          compare = this->compare_callback.function(current->data, data, this->compare_callback.user_data);
          if (compare == DS_COMPARE_EQUAL) {
               CircularBuffer_Destroy(circular_buffer);
               return;
          }
          parent = current;
          if (compare < DS_COMPARE_EQUAL) {
               current = current->left;
          } else {
               current = current->right;
          }
     }
     
     current = AvlTreeNode_Create(data, this->data_size);
     current->parent = parent;
     
     if (compare < 0) {
          parent->left = current;
     } else {
          parent->right = current;
     }

     _Rebalance(this, parent, circular_buffer);
     CircularBuffer_Destroy(circular_buffer);
     this->size++;
}

DS_Void AvlTree_Remove(AvlTree this, const DS_Generic data)
{
     CircularBuffer circular_buffer;
     AvlTreeNode current;
     AvlTreeNode parent;
     DS_Compare compare;

     circular_buffer = CircularBuffer_Create(sizeof (struct AvlTreeNode), (this->size + 2) / 2);
     parent = this->root->parent;
          
     current = this->root;
     while (current) {
          compare = this->compare_callback.function(data, current->data, this->compare_callback.user_data);
          if (compare == 0) {
               break;
          }
          parent = current;
          if (compare < 0) {
               current = current->left;
          } else {
               current = current->right;
          }
     }
     
     if (!current) {
          return;
     }
     
     if (!current->left && !current->right) {
          if (parent->left == current) {
               parent->left = NULL;
          } else {
               parent->right = NULL;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(this, parent, circular_buffer);
     } else if (!current->left) {
          if (parent->right == current) {
               parent->right = current->right;
          } else {
               parent->left = current->right;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(this, parent, circular_buffer);
     } else if (!current->right) {
          if (parent->left == current) {
               parent->left = current->left;
          } else {
               parent->right = current->left;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(this, parent, circular_buffer);
     } else {
          if (this->root->balance_factor < 0) {
               current = AvlTreeNode_GetPredecessor(current);
          } else {
               current = AvlTreeNode_GetSuccessor(current);
          }
          _Rebalance(this, current, circular_buffer);
     }

     CircularBuffer_Destroy(circular_buffer);
     this->size--;
}

// DS_Void AvlTree_TraversePreorder(AvlTree this, DS_CallbackUnary unary_callback.function,
//     DS_Generic unary_callback.user_data)
// {
// }

// DS_Void AvlTree_TraverseInorder(AvlTree this, DS_CallbackUnary unary_callback.function,
//     DS_Generic unary_callback.user_data)
// {
// }

// DS_Void AvlTree_TraversePostorder(AvlTree this, DS_CallbackUnary unary_callback.function,
//     DS_Generic unary_callback.user_data)
// {
// }

// DS_Void AvlTree_TraverseLevelorder(AvlTree this, DS_CallbackUnary unary_callback.function,
//     DS_Generic unary_callback.user_data)
// {
// }


static DS_Void _RotateRight(AvlTree this, AvlTreeNode node)
{
     AvlTreeNode left;

     left = node->left;

     node->left = left->right;
     if (node->left) {
          node->left->parent = node;
     }

     left->parent = node->parent;
     if (left->parent) {
          if (left->parent->left == node) {
               left->parent->left = left;
          } else {
               left->parent->right = left;
          }
     } else {
          this->root = left;
     }

     node->parent = left;
     left->right = node;
}

static DS_Void _RotateLeftRight(AvlTree this, AvlTreeNode node)
{
     AvlTreeNode left;
     AvlTreeNode left_right;

     left = node->left;
     left_right = node->left->right;

     left->right = left_right->left;
     if (left->right) {
          left->right->parent = left;
     }

     node->left = left_right->right;
     if (node->left) {
          node->left->parent = node;
     }
     
     left_right->left = left;
     left->parent = left_right;

     left_right->parent = node->parent;
     if (left_right->parent) {
          if (left_right->parent->left == node) {
               left_right->parent->left = left_right;
          } else {
               left_right->parent->right = left_right;
          }
     } else {
          this->root = left_right;
     }

     node->parent = left_right;
     left_right->right = node;
}

static DS_Void _RotateLeft(AvlTree this, AvlTreeNode node)
{
     AvlTreeNode right;

     right = node->right;
     
     node->right = right->left;
     if (node->right) {
          node->right->parent = node;
     }
     
     right->parent = node->parent;
     if (right->parent) {
          if (right->parent->left == node) {
               right->parent->left = right;
          } else {
               right->parent->right = right;
          }
     } else {
          this->root = right;
     }

     node->parent = right;
     right->left = node;
}

static DS_Void _RotateRightLeft(AvlTree this, AvlTreeNode node)
{
     AvlTreeNode right;
     AvlTreeNode right_left;

     right = node->right;
     right_left = node->right->left;
     
     right->left = right_left->right;
     if (right->left) {
          right->left->parent = right;
     }

     node->right = right_left->left;
     if (node->right) {
          node->right->parent = node;
     }
     
     right_left->right = right;
     right->parent = right_left;

     right_left->parent = node->parent;
     if (right_left->parent) {
          if (right_left->parent->left == node) {
               right_left->parent->left = right_left;
          } else {
               right_left->parent->right = right_left;
          }
     } else {
          this->root = right_left;
     }
     
     node->parent = right_left;
     right_left->left = node;
}

static DS_Void _Rebalance(AvlTree this, AvlTreeNode node, CircularBuffer circular_buffer)
{
     while (node) {
          AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
          if (node->balance_factor == -2) {
               if (node->left->balance_factor == -1) {
                    _RotateRight(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
                    AvlTreeNode_UpdateBalanceFactor(node->right, circular_buffer);
               } else if (node->left->balance_factor == 1) {
                    _RotateLeftRight(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
               }
          } else if (node->balance_factor == 2) {
               if (node->right->balance_factor == 1) {
                    _RotateLeft(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
                    AvlTreeNode_UpdateBalanceFactor(node->left, circular_buffer);
               } else if (node->right->balance_factor == -1) {
                    _RotateRightLeft(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
               }
          }
          node = node->parent;
     }
}
