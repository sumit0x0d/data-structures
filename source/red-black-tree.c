#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>
#include <circular-buffer.h>

#include "red-black-tree-node.h"

typedef RedBlackTreeNode Node;

struct red_black_tree {
     Node *root;
     DS_Size data_size;
     DS_Size size;
     DS_FunctionCompare compare_function;
     void *user_data;
};

static void _RotateRight(RedBlackTree *tree, Node *node);
static void _RotateLeftRight(RedBlackTree *tree, Node *node);
static void _RotateLeft(RedBlackTree *tree, Node *node);
static void _RotateRightLeft(RedBlackTree *tree, Node *node);
static void _Rebalance(RedBlackTree *tree, Node *node);

RedBlackTree *RedBlackTree_Create(DS_Size size, DS_FunctionCompare fCompare, void *uData)
{
     RedBlackTree *tree = (RedBlackTree *)malloc(sizeof (RedBlackTree));
     if (!tree) {
          return NULL;
     }
     tree->root = NULL;
     tree->data_size = size;
     tree->size = 0;
     tree->compare_function = fCompare;
     tree->user_data = uData;
     return tree;
}

void RedBlackTree_Destroy(RedBlackTree *tree)
{
     Node *node = tree->root;
     CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), tree->size);
     free(node->data);
     CircularBuffer_PushBack(cBuffer, node);
     while (!CircularBuffer_IsEmpty(cBuffer)) {
          node = (Node *)CircularBuffer_GetFrontData(cBuffer);
          CircularBuffer_PopFront(cBuffer);
          if (node->left) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(cBuffer, node->left);
          }
          if (node->right) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(cBuffer, node->right);
          }
     }
     CircularBuffer_Destroy(cBuffer);
     free(tree);
}

DS_Size RedBlackTree_GetSize(RedBlackTree *tree)
{
     return tree->size;
}

Node *RedBlackTree_Search(RedBlackTree *tree, const DS_Data data)
{
     Node *node = tree->root;
     while (node) {
          int compare = tree->compare_function(data, node->data, tree->user_data);
          if (compare == 0) {
               return node;
          } else if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     return NULL;
}

void RedBlackTree_Insert(RedBlackTree *tree, const DS_Data data)
{
     if (!tree->root) {
          tree->root = RedBlackTreeNode_Create(data, tree->data_size);
          tree->root->parent = NULL;
          tree->root->color = 1;
          tree->size++;
          return;
     }
     Node *node = tree->root;
     Node *pNode = tree->root->parent;
     int compare = 0;
     while (node) {
          compare = tree->compare_function(data, node->data, tree->user_data);
          if (compare == 0) {
               return;
          }
          pNode = node;
          if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     node = _RedBlackTreeNode_Create(data, tree->data_size);
     node->parent = pNode;
     node->color = 0;
     compare = tree->compare_function(data, pNode->data, tree->user_data);
     if (compare < 0) {
          pNode->left = node;
     } else {
          pNode->right = node;
     }
     _Rebalance(tree, pNode);
     tree->size++;
}

// void red_black_tree_remove(RedBlackTree *tree, int data)
// {
// }

static void _RotateRight(RedBlackTree *tree, Node *node)
{
     Node *lNode = node->left;
     node->left = lNode->right;
     if (node->left) {
          node->left->parent = node;
     }
     lNode->parent = node->parent;
     if (lNode->parent) {
          if (lNode->parent->left == node) {
               lNode->parent->left = lNode;
          } else {
               lNode->parent->right = lNode;
          }
     } else {
          tree->root = lNode;
     }
     node->parent = lNode;
     lNode->right = node;
}

static void _RotateLeftRight(RedBlackTree *tree, Node *node)
{
     Node *lNode = node->left;
     Node *lrNode = node->left->right;
     lNode->right = lrNode->left;
     if (lNode->right) {
          lNode->right->parent = lNode;
     }
     node->left = lrNode->right;
     if (node->left) {
          node->left->parent = node;
     }
     lrNode->left = lNode;
     lNode->parent = lrNode;
     lrNode->parent = node->parent;
     if (lrNode->parent) {
          if (lrNode->parent->left == node) {
               lrNode->parent->left = lrNode;
          } else {
               lrNode->parent->right = lrNode;
          }
     } else {
          tree->root = lrNode;
     }
     node->parent = lrNode;
     lrNode->right = node;
}

static void _RotateLeft(RedBlackTree *tree, Node *node)
{
     Node *rNode = node->right; 
     node->right = rNode->left;
     if (node->right) {
          node->right->parent = node;
     }
     rNode->parent = node->parent;
     if (rNode->parent) {
          if (rNode->parent->left == node) {
               rNode->parent->left = rNode;
          } else {
               rNode->parent->right = rNode;
          }
     } else {
          tree->root = rNode;
     }
     node->parent = rNode;
     rNode->left = node;
}

static void _RotateRightLeft(RedBlackTree *tree, Node *node)
{
     Node *rNode = node->right;
     Node *rlNode = node->right->left;
     rNode->left = rlNode->right;
     if (rNode->left) {
          rNode->left->parent = rNode;
     }
     node->right = rlNode->left;
     if (node->right) {
          node->right->parent = node;
     }
     rlNode->right = rNode;
     rNode->parent = rlNode;
     rlNode->parent = node->parent;
     if (rlNode->parent) {
          if (rlNode->parent->left == node) {
               rlNode->parent->left = rlNode;
          } else {
               rlNode->parent->right = rlNode;
          }
     } else {
          tree->root = rlNode;
     }
     node->parent = rlNode;
     rlNode->left = node;
}

static void _Rebalance(RedBlackTree *tree, Node *node)
{
     while (node) {
          if (node->color == RED_BLACK_TREE_NODE_COLOR_RED) {
               if (node->parent->left == node) {
                    if (!node->parent->right || node->parent->right->color == 1) {
                         _RotateRight(tree, node);
                    }
                    else if (node->parent->right || node->parent->right->color == 0) {
                    }
               }
          }
          if (node->parent->left == node) {
               if (node->color == 0 &&
                    (!node->parent->right || node->parent->right->color == 1)) {
               }
               if (node->color == 0 &&
                    (node->parent->right && node->parent->right->color == 0)) {
                    node->parent->color = 1;
               }
          } else {
               if (node->color == 0 &&
                    (!node->parent->left || node->parent->left->color == 1)) {
                    _RotateLeft(tree, node);
                    _RotateRightLeft(tree, node);
                    _RotateLeftRight(tree, node);
                    _RotateRight(tree, node);
               }
               if (node->color == 0 &&
                    (node->parent->left && node->parent->left->color == 0)) {
                    node->parent->color = 1;
               }
          }
          tree->root = node->parent;
     }
}
