#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>
#include <circular-buffer.h>

#include "red-black-tree/node.h"

struct RedBlackTree {
     RedBlackTreeNode root;
     DS_Size data_size;
     DS_Size size;
     DS_CompareCallback compare_callback;
};

static DS_Void _RotateRight(RedBlackTree this, RedBlackTreeNode node);
static DS_Void _RotateLeftRight(RedBlackTree this, RedBlackTreeNode node);
static DS_Void _RotateLeft(RedBlackTree this, RedBlackTreeNode node);
static DS_Void _RotateRightLeft(RedBlackTree this, RedBlackTreeNode node);
static DS_Void _Rebalance(RedBlackTree this, RedBlackTreeNode node);

RedBlackTree RedBlackTree_Create(DS_Size size, DS_CompareCallback compare_callback)
{
     RedBlackTree this;
     
     this = (RedBlackTree)malloc(sizeof (struct RedBlackTree));
     if (!this) {
          return NULL;
     }
     
     this->root = NULL;
     this->data_size = size;
     this->size = 0;
     this->compare_callback.function = compare_callback.function;
     this->compare_callback.user_data = compare_callback.user_data;
     
     return this;
}

DS_Void RedBlackTree_Destroy(RedBlackTree this)
{
     RedBlackTreeNode node;
     CircularBuffer circular_buffer;

     node = this->root;
     circular_buffer = CircularBuffer_Create(sizeof (struct RedBlackTreeNode), this->size);
     free(node->data);
     CircularBuffer_PushBack(circular_buffer, node);

     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          node = (RedBlackTreeNode)CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (node->left) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(circular_buffer, node->left);
          }
          if (node->right) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(circular_buffer, node->right);
          }
     }
     
     CircularBuffer_Destroy(circular_buffer);
     free(this);
}

DS_Size RedBlackTree_GetSize(RedBlackTree this)
{
     return this->size;
}

RedBlackTreeNode RedBlackTree_Search(RedBlackTree this, const DS_Generic data)
{
     RedBlackTreeNode node;
     DS_Compare compare;
     
     node = this->root;
     while (node) {
          compare = this->compare_callback.function(data, node->data, this->compare_callback.user_data);
          if (compare == DS_COMPARE_EQUAL) {
               return node;
          } else if (compare == DS_COMPARE_LESS) {
               node = node->left;
          } else {
               node = node->right;
          }
     }

     return NULL;
}

DS_Void RedBlackTree_Insert(RedBlackTree this, const DS_Generic data)
{
     RedBlackTreeNode node;
     RedBlackTreeNode parent;
     DS_Compare compare;

     if (!this->root) {
          this->root = RedBlackTreeNode_Create(data, this->data_size);
          this->root->parent = NULL;
          this->root->color = 1;
          this->size++;
          return;
     }

     parent = this->root->parent;

     node = this->root;
     while (node) {
          compare = this->compare_callback.function(data, node->data, this->compare_callback.user_data);
          if (compare == 0) {
               return;
          }
          parent = node;
          if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }

     node = RedBlackTreeNode_Create(data, this->data_size);
     node->parent = parent;
     node->color = 0;
     
     compare = this->compare_callback.function(data, parent->data, this->compare_callback.user_data);
     if (compare < 0) {
          parent->left = node;
     } else {
          parent->right = node;
     }
     
     _Rebalance(this, parent);
     this->size++;
}

// DS_Void this_remove(RedBlackTree tree, int data)
// {
// }

static DS_Void _RotateRight(RedBlackTree this, RedBlackTreeNode node)
{
     RedBlackTreeNode left;

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

static DS_Void _RotateLeftRight(RedBlackTree this, RedBlackTreeNode node)
{
     RedBlackTreeNode left;
     RedBlackTreeNode left_right;

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

static DS_Void _RotateLeft(RedBlackTree this, RedBlackTreeNode node)
{
     RedBlackTreeNode right;
     
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

static DS_Void _RotateRightLeft(RedBlackTree this, RedBlackTreeNode node)
{
     RedBlackTreeNode right;
     RedBlackTreeNode right_left;

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

static DS_Void _Rebalance(RedBlackTree this, RedBlackTreeNode node)
{
     while (node) {
          if (node->color == RED_BLACK_TREE_NODE_COLOR_RED) {
               if (node->parent->left == node) {
                    if (!node->parent->right || node->parent->right->color == 1) {
                         _RotateRight(this, node);
                    } else if (node->parent->right || node->parent->right->color == 0) {
                    }
               }
          }
          if (node->parent->left == node) {
               if (node->color == 0 && (!node->parent->right || node->parent->right->color == 1)) {
               }
               if (node->color == 0 &&
                  (node->parent->right && node->parent->right->color == 0)) {
                    node->parent->color = 1;
               }
          } else {
               if (node->color == 0 && (!node->parent->left || node->parent->left->color == 1)) {
                    _RotateLeft(this, node);
                    _RotateRightLeft(this, node);
                    _RotateLeftRight(this, node);
                    _RotateRight(this, node);
               }
               if (node->color == 0 && (node->parent->left && node->parent->left->color == 0)) {
                    node->parent->color = 1;
               }
          }
          this->root = node->parent;
     }
}
