#include <stdlib.h>
#include <string.h>

#include "node.h"

RedBlackTreeNode RedBlackTreeNode_Create(const void *data, size_t data_size)
{
     RedBlackTreeNode this;
     
     this = (RedBlackTreeNode)malloc(sizeof (RedBlackTreeNode));
     if (!this) {
          return NULL;
     } 
     
     this->data = malloc(data_size);
     if (!this->data) {
          free(this);
          return NULL;
     }
     
     memcpy(this->data, data, data_size);
     this->left = NULL;
     this->right = NULL; 
     
     return this;
}

void RedBlackTreeNode_Destroy(RedBlackTreeNode this)
{
     free(this->data);
     free(this);
}
