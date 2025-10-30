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

DS_Void BinaryTree_Destroy(BinaryTree tree)
{
     free(tree);
}

DS_Void BinaryTree_InsertLeft(BinaryTree this, BinaryTreeNode node, const DS_Generic data)
{
     node->left = BinaryTreeNode_Create(data, this->data_size);
     this->size++;
}

DS_Void BinaryTree_InsertRight(BinaryTree this, BinaryTreeNode node, const DS_Generic data)
{
     node->right = BinaryTreeNode_Create(data, this->data_size);
     this->size++;
}

DS_Void BinaryTree_Remove(BinaryTree this, BinaryTreeNode node)
{
     if (node == node->parent->left) {
          node->parent->left = node->left;
     }
     
     if (node == node->parent->right) {

     }
     
     BinaryTreeNode_Destroy(node);
}