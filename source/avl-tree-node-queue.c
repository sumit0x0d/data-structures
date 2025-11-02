#include <stdlib.h>
#include <string.h>

#include <avl-tree-node-queue.h>

AvlTreeNodeQueue AvlTreeNodeQueue_Create(DS_Size capacity)
{
     AvlTreeNodeQueue queue;

     queue = (AvlTreeNodeQueue)malloc(sizeof (struct AvlTreeNodeQueue));
     if (!queue) {
          return NULL;
     }

     queue->base = (AvlTreeNode *)malloc(sizeof (struct AvlTreeNode) * capacity);
     if (!queue->base) {
          free(queue);
          return NULL;
     }

     queue->front = 0;
     queue->back = 0;
     queue->capacity = capacity;

     return queue;
}

DS_Void AvlTreeNodeQueue_Destroy(AvlTreeNodeQueue queue)
{
     free(queue->base);
     free(queue);
}

DS_Bool AvlTreeNodeQueue_IsEmpty(AvlTreeNodeQueue this)
{
     if (this->front == this->back) {
          return DS_BOOL_TRUE;
     }

     return DS_BOOL_FALSE;
}

DS_Void AvlTreeNodeQueue_Enqueue(AvlTreeNodeQueue this, AvlTreeNode node)
{
     this->base[this->back] = node;
     this->back = (this->back + 1) % this->capacity;
}

DS_Void AvlTreeNodeQueue_Dequeue(AvlTreeNodeQueue this)
{
     this->front = (this->front + 1) % this->capacity;
}