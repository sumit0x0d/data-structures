#include <stdlib.h>

#include <binary-tree-node.h>

struct BinaryTreeNode {
     DS_Generic data;
     BinaryTreeNode parent;
     BinaryTreeNode left;
     BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
     BinaryTreeNode self;

     self = (BinaryTreeNode)malloc(sizeof (BinaryTreeNode));
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

DS_Void BinaryTreeNode_Destroy(BinaryTreeNode self)
{
     free(self->data);
     free(self);
}