#include <assert.h>
#include <stdlib.h>

#include <binary-tree-node.h>

struct BinaryTree {
     BinaryTreeNode root;
     DS_Size data_size;
     DS_Size size;
};

BinaryTree BinaryTree_Create(DS_Size data_size)
{
     BinaryTree self;

     self = (BinaryTree)malloc(sizeof (struct BinaryTree));
     if (!self) {
          return NULL;
     }

     self->root = NULL;
     self->data_size = data_size;
     self->size = 0;
     
     return self;
}

DS_Void BinaryTree_Destroy(BinaryTree tree)
{
     free(tree);
}

DS_Void BinaryTree_InsertLeft(BinaryTree self, BinaryTreeNode node, const DS_Generic data)
{
     node->left = BinaryTreeNode_Create(data, self->data_size);
     self->size++;
}

DS_Void BinaryTree_InsertRight(BinaryTree self, BinaryTreeNode node, const DS_Generic data)
{
     node->right = BinaryTreeNode_Create(data, self->data_size);
     self->size++;
}

DS_Void BinaryTree_Remove(BinaryTree self, BinaryTreeNode node)
{
     if (node == node->parent->left) {
          node->parent->left = node->left;
     }
     
     if (node == node->parent->right) {

     }
     
     BinaryTreeNode_Destroy(node);
}