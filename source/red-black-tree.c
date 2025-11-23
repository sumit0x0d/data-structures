#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>

#include "red-black-tree/node.h"
#include "red-black-tree/node-queue.h"

struct RedBlackTree {
     RedBlackTreeNode *root;
     size_t data_size;
     size_t size;
     RedBlackTreeCompareCallback compare_callback;
};

static void _RotateRight(RedBlackTree *this, RedBlackTreeNode *node);
static void _RotateLeftRight(RedBlackTree *this, RedBlackTreeNode *node);
static void _RotateLeft(RedBlackTree *this, RedBlackTreeNode *node);
static void _RotateRightLeft(RedBlackTree *this, RedBlackTreeNode *node);
static void _Rebalance(RedBlackTree *this, RedBlackTreeNode *node);

RedBlackTree *RedBlackTree_Create(size_t size, RedBlackTreeCompareCallback compare_callback)
{
     RedBlackTree *this;

     this = (RedBlackTree *)malloc(sizeof (RedBlackTree));
     if (!this) {
          return NULL;
     }

     this->root = NULL;
     this->data_size = size;
     this->size = 0;
     this->compare_callback = compare_callback;

     return this;
}

void RedBlackTree_Destroy(RedBlackTree *this)
{
     RedBlackTreeNode *node;
     RedBlackTreeNodeQueue *node_queue;

     node = this->root;
     node_queue = RedBlackTreeNodeQueue_Create(this->size);
     free(node->data);
     RedBlackTreeNodeQueue_Enqueue(node_queue, node);

     while (!RedBlackTreeNodeQueue_IsEmpty(node_queue)) {
          node = node_queue->base[node_queue->front];
          RedBlackTreeNodeQueue_Dequeue(node_queue);
          if (node->left) {
               RedBlackTreeNode_Destroy(node);
               // RedBlackTreeNodeQueue_Enqueue(node_queue, node->left);
          }
          if (node->right) {
               RedBlackTreeNode_Destroy(node);
               // RedBlackTreeNodeQueue_Enqueue(node_queue, node->right);
          }
     }

     RedBlackTreeNodeQueue_Destroy(node_queue);
     free(this);
}

size_t RedBlackTree_GetSize(RedBlackTree *this)
{
     return this->size;
}

RedBlackTreeNode *RedBlackTree_Search(RedBlackTree *this, const void *data)
{
     RedBlackTreeNode *node;
     RedBlackTreeCompare compare;

     node = this->root;
     while (node) {
          compare = this->compare_callback.function(data, node->data, this->compare_callback.user_data);
          if (compare == RED_BLACK_TREE_COMPARE_EQUAL) {
               return node;
          } else if (compare == RED_BLACK_TREE_COMPARE_LESS) {
               node = node->left;
          } else {
               node = node->right;
          }
     }

     return NULL;
}

void RedBlackTree_Insert(RedBlackTree *this, const void *data)
{
     RedBlackTreeNode *node;
     RedBlackTreeNode *parent;
     RedBlackTreeCompare compare;

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

// void this_remove(RedBlackTree tree, int data)
// {
// }

static void _RotateRight(RedBlackTree *this, RedBlackTreeNode *node)
{
     RedBlackTreeNode *left;

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

static void _RotateLeftRight(RedBlackTree *this, RedBlackTreeNode *node)
{
     RedBlackTreeNode *left;
     RedBlackTreeNode *left_right;

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

static void _RotateLeft(RedBlackTree *this, RedBlackTreeNode *node)
{
     RedBlackTreeNode *right;

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

static void _RotateRightLeft(RedBlackTree *this, RedBlackTreeNode *node)
{
     RedBlackTreeNode *right;
     RedBlackTreeNode *right_left;

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

static void _Rebalance(RedBlackTree *this, RedBlackTreeNode *node)
{
     while (node) {
          if (node->color == RED_BLACK_TREE_NODE_COLOR_RED) {
               if (node->parent->left == node) {
                    if (!node->parent->right || node->parent->right->color == RED_BLACK_TREE_NODE_COLOR_BLACK) {
                         _RotateRight(this, node);
                    } else if (node->parent->right || node->parent->right->color == RED_BLACK_TREE_NODE_COLOR_RED) {
                    }
               }
          }
          if (node->parent->left == node) {
               if (node->color == RED_BLACK_TREE_NODE_COLOR_RED
                    && (!node->parent->right || node->parent->right->color == RED_BLACK_TREE_NODE_COLOR_BLACK)) {
               }
               if (node->color == RED_BLACK_TREE_NODE_COLOR_RED
                    && (node->parent->right && node->parent->right->color == RED_BLACK_TREE_NODE_COLOR_RED)) {
                    node->parent->color = RED_BLACK_TREE_NODE_COLOR_BLACK;
               }
          } else {
               if (node->color == RED_BLACK_TREE_NODE_COLOR_RED
                    && (!node->parent->left || node->parent->left->color == RED_BLACK_TREE_NODE_COLOR_BLACK)) {
                    _RotateLeft(this, node);
                    _RotateRightLeft(this, node);
                    _RotateLeftRight(this, node);
                    _RotateRight(this, node);
               }
               if (node->color == RED_BLACK_TREE_NODE_COLOR_RED
                    && (node->parent->left && node->parent->left->color == RED_BLACK_TREE_NODE_COLOR_RED)) {
                    node->parent->color = RED_BLACK_TREE_NODE_COLOR_BLACK;
               }
          }
          this->root = node->parent;
     }
}
