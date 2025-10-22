#include <stdlib.h>
#include <string.h>

#include "red-black-tree-node.h"

RedBlackTreeNode RedBlackTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
     RedBlackTreeNode self;
     
     self = (RedBlackTreeNode)malloc(sizeof (RedBlackTreeNode));
     if (!self) {
          return NULL;
     } 
     
     self->data = malloc(data_size);
     if (!self->data) {
          free(self);
          return NULL;
     }
     
     memcpy(self->data, data, data_size);
     self->left = NULL;
     self->right = NULL; 
     
     return self;
}

DS_Void RedBlackTreeNode_Destroy(RedBlackTreeNode self)
{
     free(self->data);
     free(self);
}
