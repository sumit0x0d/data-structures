#ifndef DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H

#include <stdbool.h>

#include "node.h"

typedef struct AvlTreeNodeQueue {
   AvlTreeNode **base;
   size_t front;
   size_t back;
   size_t capacity;
} AvlTreeNodeQueue;

AvlTreeNodeQueue *AvlTreeNodeQueue_Create(size_t capacity);
void AvlTreeNodeQueue_Destroy(AvlTreeNodeQueue *this);

bool AvlTreeNodeQueue_IsEmpty(AvlTreeNodeQueue *this);
void AvlTreeNodeQueue_Enqueue(AvlTreeNodeQueue *this, AvlTreeNode *node);
void AvlTreeNodeQueue_Dequeue(AvlTreeNodeQueue *this);

#endif
