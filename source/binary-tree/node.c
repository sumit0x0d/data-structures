#include <stdlib.h>

#include "node.h"

struct BinaryTreeNode {
     void *data;
     BinaryTreeNode parent;
     BinaryTreeNode left;
     BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(const void *data, size_t data_size)
{
     BinaryTreeNode this;

     this = (BinaryTreeNode)malloc(sizeof (BinaryTreeNode));
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

void BinaryTreeNode_Destroy(BinaryTreeNode this)
{
     free(this->data);
     free(this);
}