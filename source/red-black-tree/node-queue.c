#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node-queue.h"

RedBlackTreeNodeQueue RedBlackTreeNodeQueue_Create(size_t capacity)
{
     RedBlackTreeNodeQueue queue;

     queue = (RedBlackTreeNodeQueue)malloc(sizeof (struct RedBlackTreeNodeQueue));
     if (!queue) {
          return NULL;
     }

     queue->base = (RedBlackTreeNode *)malloc(sizeof (struct RedBlackTreeNode) * capacity);
     if (!queue->base) {
          free(queue);
          return NULL;
     }

     queue->front = 0;
     queue->back = 0;
     queue->capacity = capacity;

     return queue;
}

void RedBlackTreeNodeQueue_Destroy(RedBlackTreeNodeQueue queue)
{
     free(queue->base);
     free(queue);
}

bool RedBlackTreeNodeQueue_IsEmpty(RedBlackTreeNodeQueue this)
{
     if (this->front == this->back) {
          return true;
     }

     return false;
}

void RedBlackTreeNodeQueue_Enqueue(RedBlackTreeNodeQueue this, RedBlackTreeNode node)
{
     this->base[this->back] = node;
     this->back = (this->back + 1) % this->capacity;
}

void RedBlackTreeNodeQueue_Dequeue(RedBlackTreeNodeQueue this)
{
     this->front = (this->front + 1) % this->capacity;
}