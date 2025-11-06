#ifndef DATA_STRUCTURES_AVL_TREE_NODE_STACK_H
#define DATA_STRUCTURES_AVL_TREE_NODE_STACK_H

#include <stdbool.h>

#include "node.h"

typedef struct AvlTreeNodeStack {
     AvlTreeNode **base;
     size_t capacity;
     size_t size;
} AvlTreeNodeStack;

AvlTreeNodeStack *AvlTreeNodeStack_Create(size_t capacity);
void AvlTreeNodeStack_Destroy(AvlTreeNodeStack *this);

bool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack *this);
void AvlTreeNodeStack_Push(AvlTreeNodeStack *this, AvlTreeNode *node);
void AvlTreeNodeStack_pop(AvlTreeNodeStack *this);

#endif