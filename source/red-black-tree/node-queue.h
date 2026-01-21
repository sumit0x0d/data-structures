#ifndef DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_QUEUE_H

#include <stdbool.h>

#include "node.h"

typedef struct RedBlackTreeNodeQueue {
   RedBlackTreeNode **base;
   size_t front;
   size_t back;
   size_t capacity;
} RedBlackTreeNodeQueue;

RedBlackTreeNodeQueue *RedBlackTreeNodeQueue_Create(size_t capacity);
void RedBlackTreeNodeQueue_Destroy(RedBlackTreeNodeQueue *this);

bool RedBlackTreeNodeQueue_IsEmpty(RedBlackTreeNodeQueue *this);
void RedBlackTreeNodeQueue_Enqueue(RedBlackTreeNodeQueue *this, RedBlackTreeNode *node);
void RedBlackTreeNodeQueue_Dequeue(RedBlackTreeNodeQueue *this);

#endif
