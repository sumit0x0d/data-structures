#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>
#include <circular-buffer.h>
#include <stack.h>

typedef AvlTreeNode Node;
typedef AvlTreeCompare Compare;

struct avl_tree_node {
     void *data;
     Node *parent;
     Node *left;
     Node *right;
     int balance_factor;
};

struct avl_tree {
     Node *root;
     size_t data_size;
     size_t size;
     Compare compare;
     void *user_data;
};

static Node *_AvlTreeNode_Create(const void *data, size_t dSize);
static void _AvlTreeNode_Destroy(Node *node);

static size_t _AvlTreeNode_GetHeight(Node *node, CircularBuffer *cBuffer);
static void _AvlTreeNode_UpdateBalanceFactor(Node *node, CircularBuffer *cBuffer);
static Node *_AvlTreeNode_GetPredecessor(Node *node);
static Node *_AvlTreeNode_GetSuccessor(Node *node);

static void _AvlTree_Rebalance(AvlTree *aTree, Node *node, CircularBuffer *cBuffer);
static void _AvlTree_RotateRight(AvlTree *aTree, Node *node);
static void _AvlTree_RotateLeftRight(AvlTree *aTree, Node *node);
static void _AvlTree_RotateLeft(AvlTree *aTree, Node *node);
static void _AvlTree_RotateRightLeft(AvlTree *aTree, Node *node);

AvlTree *AvlTree_Create(size_t dSize, Compare compare, void *uData)
{
     AvlTree *aTree = (AvlTree *)malloc(sizeof (AvlTree));
     assert(aTree);
     aTree->root = NULL;
     aTree->data_size = dSize;
     aTree->size = 0;
     aTree->compare = compare;
     aTree->user_data = uData;
     return aTree;
}

void AvlTree_Destroy(AvlTree *aTree)
{
     CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), aTree->size);
     Node *node = aTree->root;
     free(node->data);
     CircularBuffer_PushBack(cBuffer, node);
     while (!CircularBuffer_IsEmpty(cBuffer)) {
          node = (Node *)CircularBuffer_GetFrontData(cBuffer);
          CircularBuffer_PopFront(cBuffer);
          if (node->left) {
               free(node->data);
               CircularBuffer_PushBack(cBuffer, node->left);
          }
          if (node->right) {
               free(node->data);
               CircularBuffer_PushBack(cBuffer, node->right);
          }
     }
     CircularBuffer_Destroy(cBuffer);
     free(aTree);
}

Node *AvlTree_Search(AvlTree *aTree, const void *data)
{
     Node *node = aTree->root;
     while (node) {
          switch (aTree->compare(node->data, data, aTree->user_data)) {
          case -1:
               node = node->left;
               break;
          case 0:
               return node;
          case 1:
               node = node->right;
               break;
          }
     }
     return NULL;
}

void AvlTree_Insert(AvlTree *aTree, const void *data)
{
     if (!aTree->root) {
          aTree->root = _AvlTreeNode_Create(data, aTree->data_size);
          aTree->root->parent = NULL;
          aTree->size++;
          return;
     }
     CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), (aTree->size + 2) / 2);
     Node *node = aTree->root;
     Node *pnode = aTree->root->parent;
     int compare = 0;
     while (node) {
          compare = aTree->compare(node->data, data, aTree->user_data);
          if (compare == 0) {
               CircularBuffer_Destroy(cBuffer);
               return;
          }
          pnode = node;
          if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     node = _AvlTreeNode_Create(data, aTree->data_size);
     node->parent = pnode;
     if (compare < 0) {
          pnode->left = node;
     } else {
          pnode->right = node;
     }
     _AvlTree_Rebalance(aTree, pnode, cBuffer);
     CircularBuffer_Destroy(cBuffer);
     aTree->size++;
}

void AvlTree_Remove(AvlTree *aTree, const void *data)
{
     CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), (aTree->size + 2) / 2);
     Node *node = aTree->root;
     Node *pnode = aTree->root->parent;
     while (node) {
          int compare = aTree->compare(data, node->data, aTree->user_data);
          if (compare == 0) {
               break;
          }
          pnode = node;
          if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     if (!node) {
          return;
     }
     if (!node->left && !node->right) {
          if (pnode->left == node) {
               pnode->left = NULL;
          } else {
               pnode->right = NULL;
          }
          _AvlTreeNode_Destroy(node);
          _AvlTree_Rebalance(aTree, pnode, cBuffer);
     }
     else if (!node->left) {
          if (pnode->right == node) {
               pnode->right = node->right;
          } else {
               pnode->left = node->right;
          }
          _AvlTreeNode_Destroy(node);
          _AvlTree_Rebalance(aTree, pnode, cBuffer);
     }
     else if (!node->right) {
          if (pnode->left == node) {
               pnode->left = node->left;
          }
          else {
               pnode->right = node->left;
          }
          _AvlTreeNode_Destroy(node);
          _AvlTree_Rebalance(aTree, pnode, cBuffer);
     } else {
          if (aTree->root->balance_factor < 0) {
               node = _AvlTreeNode_GetPredecessor(node);
          } else {
               node = _AvlTreeNode_GetSuccessor(node);
          }
          _AvlTree_Rebalance(aTree, node, cBuffer);
     }
     CircularBuffer_Destroy(cBuffer);
     aTree->size--;
}

void AvlTree_TraversePreorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData)
{
     Node *node = aTree->root;
     Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               atTraverse(node->data, uData);
               node = node->left;
          } else {
               node = (Node *)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

void AvlTree_TraverseInorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData)
{
     Node *node = aTree->root;
     Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               node = node->left;
          } else {
               node = (Node *)Stack_GetTop(stack);
               Stack_Pop(stack);
               atTraverse(node->data, uData);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

void AvlTree_TraversePostorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData)
{
     Node *node = aTree->root;
     Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               atTraverse(node->data, uData);
               node = node->left;
          } else {
               node = (Node *)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

void AvlTree_TraverseLevelorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData)
{
     Node *node = aTree->root;
     CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), aTree->size);
     atTraverse(node->data, uData);
     CircularBuffer_PushBack(cBuffer, node);
     while (!CircularBuffer_IsEmpty(cBuffer)) {
          node = CircularBuffer_GetFrontData(cBuffer);
          CircularBuffer_PopFront(cBuffer);
          if (node->left) {
               atTraverse(node->data, uData);
               CircularBuffer_PushBack(cBuffer, node->left);
          }
          if (node->right) {
               atTraverse(node->data, uData);
               CircularBuffer_PushBack(cBuffer, node->right);
          }
     }
     CircularBuffer_Destroy(cBuffer);
}

static Node *_AvlTreeNode_Create(const void *data, size_t dSize)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);
     node->data = malloc(dSize);
     assert(node->data);
     memcpy(node->data, data, dSize);
     node->left = NULL;
     node->right = NULL;
     node->balance_factor = 0;
     return node;
}

static void _AvlTreeNode_Destroy(Node *node)
{
     free(node->data);
     free(node);
}

static size_t _AvlTreeNode_GetHeight(Node *node, CircularBuffer *cBuffer)
{
     size_t height = 0;
     CircularBuffer_PushBack(cBuffer, node);
     while (!CircularBuffer_IsEmpty(cBuffer)) {
          node = CircularBuffer_GetFrontData(cBuffer);
          CircularBuffer_PopFront(cBuffer);
          if (node->left) {
               CircularBuffer_PushBack(cBuffer, node->left);
          }
          if (node->right) {
               CircularBuffer_PushBack(cBuffer, node->right);
          }
          height++;
     }
     return height;
}

static void _AvlTreeNode_UpdateBalanceFactor(Node *node, CircularBuffer *cBuffer)
{
     size_t lnheight = 0;
     size_t rnheight = 0;
     if (node->left) {
          lnheight = _AvlTreeNode_GetHeight(node->left, cBuffer);
     }
     if (node->right) {
          rnheight = _AvlTreeNode_GetHeight(node->right, cBuffer);
     }
     node->balance_factor = (int)(lnheight - rnheight);
}

static Node *_AvlTreeNode_GetPredecessor(Node *node)
{
     Node *lnode = node->left;
     Node *pnode = node;
     free(node->data);
     node = lnode;
     while (node->right) {
          node = node->right;
     }
     pnode->data = node->data;
     lnode = node->left;
     pnode = node->parent;
     pnode->right = lnode;
     if (lnode) {
          lnode->parent = pnode;
     }
     free(node);
     return pnode;
}

static Node *_AvlTreeNode_GetSuccessor(Node *node)
{
     Node *rNode = node->right;
     Node *pnode = node;
     free(node->data);
     node = rNode;
     while (node->left) {
          node = node->left;
     }
     pnode->data = node->data;
     rNode = node->right;
     pnode = node->parent;
     pnode->left = rNode;
     if (rNode) {
          rNode->parent = pnode;
     }
     free(node);
     return pnode;
}

static void _AvlTree_RotateRight(AvlTree *tree, Node *node)
{
     Node *lnode = node->left;
     node->left = lnode->right;
     if (node->left) {
          node->left->parent = node;
     }
     lnode->parent = node->parent;
     if (lnode->parent) {
          if (lnode->parent->left == node) lnode->parent->left = lnode;
          else lnode->parent->right = lnode;
     } else {
          tree->root = lnode;
     }
     node->parent = lnode;
     lnode->right = node;
}

static void _AvlTree_RotateLeftRight(AvlTree *aTree, Node *node)
{
     Node *lnode = node->left;
     Node *lrNode = node->left->right;
     lnode->right = lrNode->left;
     if (lnode->right) {
          lnode->right->parent = lnode;
     }
     node->left = lrNode->right;
     if (node->left) {
          node->left->parent = node;
     }
     lrNode->left = lnode;
     lnode->parent = lrNode;
     lrNode->parent = node->parent;
     if (lrNode->parent) {
          if (lrNode->parent->left == node) {
               lrNode->parent->left = lrNode;
          } else {
               lrNode->parent->right = lrNode;
          }
     } else {
          aTree->root = lrNode;
     }
     node->parent = lrNode;
     lrNode->right = node;
}

static void _AvlTree_RotateLeft(AvlTree *aTree, Node *node)
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
          aTree->root = rNode;
     }
     node->parent = rNode;
     rNode->left = node;
}

static void _AvlTree_RotateRightLeft(AvlTree *aTree, Node *node)
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
          aTree->root = rlNode;
     }
     node->parent = rlNode;
     rlNode->left = node;
}

static void _AvlTree_Rebalance(AvlTree *aTree, Node *node, CircularBuffer *cBuffer)
{
     while (node) {
          _AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
          if (node->balance_factor == -2) {
               if (node->left->balance_factor == -1) {
                    _AvlTree_RotateRight(aTree, node);
                    _AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                    _AvlTreeNode_UpdateBalanceFactor(node->right, cBuffer);
               } else if (node->left->balance_factor == 1) {
                    _AvlTree_RotateLeftRight(aTree, node);
                    _AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
               }
          } else if (node->balance_factor == 2) {
               if (node->right->balance_factor == 1) {
                    _AvlTree_RotateLeft(aTree, node);
                    _AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                    _AvlTreeNode_UpdateBalanceFactor(node->left, cBuffer);
               }
               else if (node->right->balance_factor == -1) {
                    _AvlTree_RotateRightLeft(aTree, node);
                    _AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
               }
          }
          node = node->parent;
     }
}
