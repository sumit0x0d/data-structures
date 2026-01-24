#ifndef DATA_STRUCTURES_AVL_TREE_NODE_STACK_H
#define DATA_STRUCTURES_AVL_TREE_NODE_STACK_H

#include "node.h"

typedef struct AvlTreeNodeStack {
   AvlTreeNode **base;
   size_t capacity;
   size_t size;
} AvlTreeNodeStack;

typedef enum {
   AVL_TREE_NODE_STACK_BOOL_FALSE = 0,
   AVL_TREE_NODE_STACK_BOOL_TRUE = 1
} AvlTreeNodeStackBool;

AvlTreeNodeStack *AvlTreeNodeStack_Create(size_t capacity);
void AvlTreeNodeStack_Destroy(AvlTreeNodeStack *this);

AvlTreeNodeStackBool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack *this);
void AvlTreeNodeStack_Push(AvlTreeNodeStack *this, AvlTreeNode *node);
void AvlTreeNodeStack_pop(AvlTreeNodeStack *this);

#endif
