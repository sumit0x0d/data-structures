#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "node-queue.h"

static size_t _GetHeight(AvlTreeNode *this, AvlTreeNodeQueue *queue);

AvlTreeNode *AvlTreeNode_Create(const void *data, size_t data_size)
{
     AvlTreeNode *this;

     this = (AvlTreeNode *)malloc(sizeof (AvlTreeNode));
     if (!this) {
          return NULL;
     }

     this->data = malloc(data_size);
     if (!this->data){
          free(this);
          return NULL;
     }

     memcpy(this->data, data, data_size);
     this->left = NULL;
     this->right = NULL;
     this->balance_factor = 0;

     return this;
}

void AvlTreeNode_Destroy(AvlTreeNode *this)
{
     free(this->data);
     free(this);
}

void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode *this, size_t queue_capacity)
{
     AvlTreeNodeQueue *queue;

     queue = AvlTreeNodeQueue_Create(queue_capacity);

     if (this->left) {
          this->left->height = _GetHeight(this->left, queue);
     } else {
          this->left->height = 0;
     }

     if (this->right) {
          this->right->height = _GetHeight(this->right, queue);
     } else {
          this->right->height = 0;
     }

     this->balance_factor = (AvlTreeNodeBalanceFactor)(this->left->height - this->right->height);
     AvlTreeNodeQueue_Destroy(queue);
}

AvlTreeNode *AvlTreeNode_GetPredecessor(AvlTreeNode *this)
{
     AvlTreeNode *left;
     AvlTreeNode *previous;

     left = this->left;
     previous = this;
     free(this->data);
     this = left;

     while (this->right) {
          this = this->right;
     }
     
     previous->data = this->data;
     left = this->left;
     previous = this->parent;
     previous->right = left;
     
     if (left) {
          left->parent = previous;
     }
     
     free(this);
     
     return previous;
}

AvlTreeNode *AvlTreeNode_GetSuccessor(AvlTreeNode *this)
{
     AvlTreeNode *right;
     AvlTreeNode *previous;

     right = this->right;
     previous = this;
     free(this->data);
     this = right;

     while (this->left) {
          this = this->left;
     }

     previous->data = this->data;
     right = this->right;
     previous = this->parent;
     previous->left = right;

     if (right) {
          right->parent = previous;
     }

     free(this);

     return previous;
}

static size_t _GetHeight(AvlTreeNode *this, AvlTreeNodeQueue *queue)
{
     size_t height;

     height = 0;
     AvlTreeNodeQueue_Enqueue(queue, this);

     while (!AvlTreeNodeQueue_IsEmpty(queue)) {
          this = queue->base[queue->front];
          AvlTreeNodeQueue_Dequeue(queue);
          if (this->left) {
               AvlTreeNodeQueue_Enqueue(queue, this->left);
          }
          if (this->right) {
               AvlTreeNodeQueue_Enqueue(queue, this->right);
          }
          height++;
     }

     return height;
}