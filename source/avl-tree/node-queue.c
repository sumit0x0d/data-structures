#include <stdlib.h>
#include <string.h>

#include "node-queue.h"

AvlTreeNodeQueue *AvlTreeNodeQueue_Create(size_t capacity)
{
   AvlTreeNodeQueue *queue;

   queue = (AvlTreeNodeQueue *)malloc(sizeof (AvlTreeNodeQueue));
   if (!queue) {
      return NULL;
   }

   queue->base = (AvlTreeNode **)malloc(sizeof (struct AvlTreeNode *) * capacity);
   if (!queue->base) {
      free(queue);
      return NULL;
   }

   queue->front = 0;
   queue->back = 0;
   queue->capacity = capacity;

   return queue;
}

void AvlTreeNodeQueue_Destroy(AvlTreeNodeQueue *this)
{
   free(this->base);
   free(this);
}

AvlTreeNodeQueueBool AvlTreeNodeQueue_IsEmpty(AvlTreeNodeQueue *this)
{
   if (this->front == this->back) {
      return AVL_TREE_NODE_QUEUE_BOOL_TRUE;
   }

   return AVL_TREE_NODE_QUEUE_BOOL_FALSE;
}

void AvlTreeNodeQueue_Enqueue(AvlTreeNodeQueue *this, AvlTreeNode *node)
{
   this->base[this->back] = node;
   this->back = (this->back + 1) % this->capacity;
}

void AvlTreeNodeQueue_Dequeue(AvlTreeNodeQueue *this)
{
   this->front = (this->front + 1) % this->capacity;
}
