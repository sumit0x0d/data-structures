#ifndef DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H

#include "node.h"

typedef struct RedBlackTreeNodeQueue {
   RedBlackTreeNode **base;
   size_t front;
   size_t back;
   size_t capacity;
} RedBlackTreeNodeQueue;

typedef enum {
   RED_BLACK_TREE_NODE_QUEUE_BOOL_FALSE = 0,
   RED_BLACK_TREE_NODE_QUEUE_BOOL_TRUE = 1
} RedBlackTreeNodeQueueBool;

RedBlackTreeNodeQueue *RedBlackTreeNodeQueue_Create(size_t capacity);
void RedBlackTreeNodeQueue_Destroy(RedBlackTreeNodeQueue *this);

RedBlackTreeNodeQueueBool RedBlackTreeNodeQueue_IsEmpty(RedBlackTreeNodeQueue *this);
void RedBlackTreeNodeQueue_Enqueue(RedBlackTreeNodeQueue *this, RedBlackTreeNode *node);
void RedBlackTreeNodeQueue_Dequeue(RedBlackTreeNodeQueue *this);

#endif
