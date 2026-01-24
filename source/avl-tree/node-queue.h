#ifndef DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H

#include "node.h"

typedef struct AvlTreeNodeQueue {
   AvlTreeNode **base;
   size_t front;
   size_t back;
   size_t capacity;
} AvlTreeNodeQueue;

typedef enum {
   AVL_TREE_NODE_QUEUE_BOOL_FALSE = 0,
   AVL_TREE_NODE_QUEUE_BOOL_TRUE = 1
} AvlTreeNodeQueueBool;

AvlTreeNodeQueue *AvlTreeNodeQueue_Create(size_t capacity);
void AvlTreeNodeQueue_Destroy(AvlTreeNodeQueue *this);

AvlTreeNodeQueueBool AvlTreeNodeQueue_IsEmpty(AvlTreeNodeQueue *this);
void AvlTreeNodeQueue_Enqueue(AvlTreeNodeQueue *this, AvlTreeNode *node);
void AvlTreeNodeQueue_Dequeue(AvlTreeNodeQueue *this);

#endif
