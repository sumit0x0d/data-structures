#include <assert.h>
#include <stdlib.h>

#include "binary-tree/node.h"

struct BinaryTree {
   BinaryTreeNode root;
   size_t data_size;
   size_t size;
};

BinaryTree BinaryTree_Create(size_t data_size)
{
   BinaryTree this;

   this = (BinaryTree)malloc(sizeof (struct BinaryTree));
   if (!this) {
      return NULL;
   }

   this->root = NULL;
   this->data_size = data_size;
   this->size = 0;

   return this;
}

void BinaryTree_Destroy(BinaryTree tree)
{
   free(tree);
}

void BinaryTree_InsertLeft(BinaryTree this, BinaryTreeNode node, const void *data)
{
   node->left = BinaryTreeNode_Create(data, this->data_size);
   this->size++;
}

void BinaryTree_InsertRight(BinaryTree this, BinaryTreeNode node, const void *data)
{
   node->right = BinaryTreeNode_Create(data, this->data_size);
   this->size++;
}

void BinaryTree_Remove(BinaryTree this, BinaryTreeNode node)
{
   if (node == node->parent->left) {
      node->parent->left = node->left;
   }

   if (node == node->parent->right) {

   }

   BinaryTreeNode_Destroy(node);
}
