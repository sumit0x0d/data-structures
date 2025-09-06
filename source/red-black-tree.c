#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>
#include <circular-buffer.h>

typedef RedBlackTreeNode Node;
typedef RedBlackTreeCompare Compare;
typedef enum red_black_tree_node_color RedBlackTreeNodeColor;
typedef RedBlackTreeNodeColor NodeColor;

enum red_black_tree_node_color {
     RED = 0,
     BLACK = 1
};

struct red_black_tree_node {
     DS_Data data;
     Node *parent;
     Node *left;
     Node *right;
     NodeColor color;
};

struct red_black_tree {
     Node *root;
     DS_Size data_size;
     DS_Size size;
     Compare compare;
     void *user_data;
};

static Node *_RedBlackTreeNode_Create(const DS_Data data, DS_Size size);
static void _RedBlackTreeNode_Destroy(Node *node);

static void _RedBlackTree_RotateRight(RedBlackTree *rbTree, Node *node);
static void _RedBlackTree_RotateLeftRight(RedBlackTree *rbTree, Node *node);
static void _RedBlackTree_RotateLeft(RedBlackTree *rbTree, Node *node);
static void _RedBlackTree_RotateRightLeft(RedBlackTree *rbTree, Node *node);
static void _RedBlackTree_Rebalance(RedBlackTree *rbTree, Node *node);

RedBlackTree *RedBlackTree_Create(DS_Size size, Compare compare, void *uData)
{
     RedBlackTree *rbTree = (RedBlackTree *)malloc(sizeof (RedBlackTree));
     assert(red_black_tree);
     rbTree->root = NULL;
     rbTree->data_size = size;
     rbTree->size = 0;
     rbTree->compare = compare;
     rbTree->user_data = uData;
     return rbTree;
}

void RedBlackTree_Destroy(RedBlackTree *rbTree)
{
     Node *node = rbTree->root;
     CircularBuffer *cBuffer = DS_CircularBuffer_Create(sizeof (Node *), rbTree->size);
     free(node->data);
     DS_CircularBuffer_PushBack(cBuffer, node);
     while (!DS_CircularBuffer_IsEmpty(cBuffer)) {
          node = (Node *)DS_CircularBuffer_GetFrontData(cBuffer);
          DS_CircularBuffer_PopFront(cBuffer);
          if (node->left) {
               _RedBlackTreeNode_Destroy(node);
               // DS_CircularBuffer_PushBack(cBuffer, node->left);
          }
          if (node->right) {
               _RedBlackTreeNode_Destroy(node);
               // DS_CircularBuffer_PushBack(cBuffer, node->right);
          }
     }
     DS_CircularBuffer_Destroy(cBuffer);
     free(rbTree);
}

DS_Size RedBlackTree_GetSize(RedBlackTree *rbTree)
{
     return rbTree->size;
}

Node *RedBlackTree_Search(RedBlackTree *rbTree, const DS_Data data)
{
     Node *node = rbTree->root;
     while (node) {
          int compare = rbTree->compare(data, node->data, rbTree->user_data);
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

void RedBlackTree_Insert(RedBlackTree *rbTree, const DS_Data data)
{
     if (!rbTree->root) {
          rbTree->root = _RedBlackTreeNode_Create(data, rbTree->data_size);
          rbTree->root->parent = NULL;
          rbTree->root->color = 1;
          rbTree->size++;
          return;
     }
     Node *node = rbTree->root;
     Node *pNode = rbTree->root->parent;
     int compare = 0;
     while (node) {
          compare = rbTree->compare(data, node->data, rbTree->user_data);
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
     node = _RedBlackTreeNode_Create(data, rbTree->data_size);
     node->parent = pNode;
     node->color = 0;
     compare = rbTree->compare(data, pNode->data, rbTree->user_data);
     if (compare < 0) {
          pNode->left = node;
     } else {
          pNode->right = node;
     }
     _RedBlackTree_Rebalance(rbTree, pNode);
     rbTree->size++;
}

// void red_black_tree_remove(RedBlackTree *rbTree, int data)
// {
// }

static Node *_RedBlackTreeNode_Create(const DS_Data data, DS_Size size)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node); 
     node->data = malloc(size);
     assert(node->data); 
     memcpy(node->data, data, size);
     node->left = NULL;
     node->right = NULL; 
     return node;
}

static void _RedBlackTreeNode_Destroy(Node *node)
{
     free(node->data);
     free(node);
}

static void _RedBlackTree_RotateRight(RedBlackTree *rbTree, Node *node)
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
          rbTree->root = lNode;
     }
     node->parent = lNode;
     lNode->right = node;
}

static void _RedBlackTree_RotateLeftRight(RedBlackTree *rbTree, Node *node)
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
          rbTree->root = lrNode;
     }
     node->parent = lrNode;
     lrNode->right = node;
}

static void _RedBlackTree_RotateLeft(RedBlackTree *rbTree, Node *node)
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
          rbTree->root = rNode;
     }
     node->parent = rNode;
     rNode->left = node;
}

static void _RedBlackTree_RotateRightLeft(RedBlackTree *rbTree, Node *node)
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
          rbTree->root = rlNode;
     }
     node->parent = rlNode;
     rlNode->left = node;
}

static void _RedBlackTree_Rebalance(RedBlackTree *rbTree, Node *node)
{
     while (node) {
          if (node->color == RED) {
               if (node->parent->left == node) {
                    if (!node->parent->right || node->parent->right->color == 1) {
                         _RedBlackTree_RotateRight(rbTree, node);
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
                    _RedBlackTree_RotateLeft(rbTree, node);
                    _RedBlackTree_RotateRightLeft(rbTree, node);
                    _RedBlackTree_RotateLeftRight(rbTree, node);
                    _RedBlackTree_RotateRight(rbTree, node);
               }
               if (node->color == 0 &&
                    (node->parent->left && node->parent->left->color == 0)) {
                    node->parent->color = 1;
               }
          }
          rbTree->root = node->parent;
     }
}
