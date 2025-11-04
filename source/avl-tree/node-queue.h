#ifndef DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H

#include "node.h"

typedef struct AvlTreeNodeQueue {
     AvlTreeNode *base;
     DS_Size front;
     DS_Size back;
     DS_Size capacity;
} * AvlTreeNodeQueue;

AvlTreeNodeQueue AvlTreeNodeQueue_Create(DS_Size capacity);
DS_Void AvlTreeNodeQueue_Destroy(AvlTreeNodeQueue this);

DS_Bool AvlTreeNodeQueue_IsEmpty(AvlTreeNodeQueue this);
DS_Void AvlTreeNodeQueue_Enqueue(AvlTreeNodeQueue this, AvlTreeNode node);
DS_Void AvlTreeNodeQueue_Dequeue(AvlTreeNodeQueue this);

#endif