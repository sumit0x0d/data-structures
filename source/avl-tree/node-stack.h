#ifndef DATA_STRUCTURES_AVL_TREE_NODE_STACK_H
#define DATA_STRUCTURES_AVL_TREE_NODE_STACK_H

#include "node.h"

typedef struct AvlTreeNodeStack {
     AvlTreeNode *base;
     DS_Size capacity;
     DS_Size size;
} * AvlTreeNodeStack;

AvlTreeNodeStack AvlTreeNodeStack_Create(DS_Size capacity);
DS_Void AvlTreeNodeStack_Destroy(AvlTreeNodeStack this);

DS_Bool AvlTreeNodeStack_IsEmpty(AvlTreeNodeStack this);
DS_Void AvlTreeNodeStack_Push(AvlTreeNodeStack this, AvlTreeNode node);
DS_Void AvlTreeNodeStack_pop(AvlTreeNodeStack this);

#endif