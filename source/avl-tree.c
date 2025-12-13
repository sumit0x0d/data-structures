#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>

#include "avl-tree/node.h"
#include "avl-tree/node-queue.h"

struct AvlTree {
     AvlTreeNode *root;
     size_t data_size;
     size_t size;
     AvlTreeCompareCallback compare_callback;
};

static void _Rebalance(AvlTree *this, AvlTreeNode *node);
static void _RotateRight(AvlTree *this, AvlTreeNode *node);
static void _RotateLeftRight(AvlTree *this, AvlTreeNode *node);
static void _RotateLeft(AvlTree *this, AvlTreeNode *node);
static void _RotateRightLeft(AvlTree *this, AvlTreeNode *node);

AvlTree *AvlTree_Create(size_t data_size, AvlTreeCompareCallback compare_callback)
{
     AvlTree *this;

     this = (AvlTree *)malloc(sizeof (AvlTree));
     if (!this) {
          return NULL;
     }

     this->root = NULL;
     this->data_size = data_size;
     this->size = 0;
     this->compare_callback = compare_callback;

     return this;
}

void AvlTree_Destroy(AvlTree *this)
{
     AvlTreeNode *node ;
     AvlTreeNodeQueue *queue;

     node = this->root;
     queue = AvlTreeNodeQueue_Create(this->size);

     free(node->data);
     AvlTreeNodeQueue_Enqueue(queue, node);

     while (!AvlTreeNodeQueue_IsEmpty(queue)) {
          node = queue->base[queue->front];
          AvlTreeNodeQueue_Dequeue(queue);
          if (node->left) {
               free(node->data);
               AvlTreeNodeQueue_Enqueue(queue, node->left);
          }
          if (node->right) {
               free(node->data);
               AvlTreeNodeQueue_Enqueue(queue, node->right);
          }
     }

     AvlTreeNodeQueue_Destroy(queue);
     free(this);
}

size_t AvlTree_GetSize(AvlTree *this)
{
     return this->size;
}

size_t AvlTree_GetDataSize(AvlTree *this)
{
     return this->data_size;
}

void *AvlTree_GetNodeData(AvlTreeNode *node)
{
     return node->data;
}

AvlTreeNode *AvlTree_Search(AvlTree *this, const void *data)
{
     AvlTreeNode *current;
     AvlTreeCompare compare;

     current = this->root;
     while (current) {
          compare = this->compare_callback.function(data, current->data, this->compare_callback.user_data);
          switch (compare) {
          case AVL_TREE_COMPARE_LESS:
               current = current->left;
               break;
          case AVL_TREE_COMPARE_EQUAL:
               return current;
          case AVL_TREE_COMPARE_GREATER:
               current = current->right;
               break;
          }
     }

     return NULL;
}

void AvlTree_Insert(AvlTree *this, const void *data)
{
     AvlTreeNode *current;
     AvlTreeNode *parent;
     AvlTreeCompare compare;

     if (!this->root) {
          this->root = AvlTreeNode_Create(data, this->data_size);
          this->root->parent = NULL;
          this->size++;
          return;
     }

     parent = this->root->parent;

     current = this->root;
     while (current) {
          compare = this->compare_callback.function(current->data, data, this->compare_callback.user_data);
          if (compare == AVL_TREE_COMPARE_EQUAL) {
               return;
          }
          parent = current;
          if (compare < AVL_TREE_COMPARE_EQUAL) {
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

     _Rebalance(this, parent);
     this->size++;
}

void AvlTree_Remove(AvlTree *this, const void *data)
{
     AvlTreeNode *current;
     AvlTreeNode *parent;
     AvlTreeCompare compare;

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
          _Rebalance(this, parent);
     } else if (!current->left) {
          if (parent->right == current) {
               parent->right = current->right;
          } else {
               parent->left = current->right;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(this, parent);
     } else if (!current->right) {
          if (parent->left == current) {
               parent->left = current->left;
          } else {
               parent->right = current->left;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(this, parent);
     } else {
          if (this->root->balance_factor < 0) {
               current = AvlTreeNode_GetPredecessor(current);
          } else {
               current = AvlTreeNode_GetSuccessor(current);
          }
          _Rebalance(this, current);
     }

     this->size--;
}

// void AvlTree_TraversePreorder(AvlTree *this, AVL_TREE_CallbackUnary unary_callback.function,
//     void *unary_callback.user_data)
// {
// }

// void AvlTree_TraverseInorder(AvlTree *this, AVL_TREE_CallbackUnary unary_callback.function,
//     void *unary_callback.user_data)
// {
// }

// void AvlTree_TraversePostorder(AvlTree *this, AVL_TREE_CallbackUnary unary_callback.function,
//     void *unary_callback.user_data)
// {
// }

// void AvlTree_TraverseLevelorder(AvlTree *this, AVL_TREE_CallbackUnary unary_callback.function,
//     void *unary_callback.user_data)
// {
// }


static void _RotateRight(AvlTree *this, AvlTreeNode *node)
{
     AvlTreeNode *left;

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

static void _RotateLeftRight(AvlTree *this, AvlTreeNode *node)
{
     AvlTreeNode *left;
     AvlTreeNode *left_right;

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

static void _RotateLeft(AvlTree *this, AvlTreeNode *node)
{
     AvlTreeNode *right;

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

static void _RotateRightLeft(AvlTree *this, AvlTreeNode *node)
{
     AvlTreeNode *right;
     AvlTreeNode *right_left;

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

static void _Rebalance(AvlTree *this, AvlTreeNode *node)
{
     size_t queue_capacity = (this->size + 2) / 2;

     while (node) {
          AvlTreeNode_UpdateBalanceFactor(node, queue_capacity);
          if (node->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY_2) {
               if (node->left->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY_1) {
                    _RotateRight(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, queue_capacity);
                    AvlTreeNode_UpdateBalanceFactor(node->right, queue_capacity);
               } else if (node->left->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY_1) {
                    _RotateLeftRight(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, queue_capacity);
               }
          } else if (node->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY_2) {
               if (node->right->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY_1) {
                    _RotateLeft(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, queue_capacity);
                    AvlTreeNode_UpdateBalanceFactor(node->left, queue_capacity);
               } else if (node->right->balance_factor == AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY_1) {
                    _RotateRightLeft(this, node);
                    AvlTreeNode_UpdateBalanceFactor(node, queue_capacity);
               }
          }
          node = node->parent;
     }
}
