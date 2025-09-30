#include <assert.h>
#include <stdlib.h>

#include <binary-tree-node.h>

struct binary_tree {
     BinaryTreeNode root;
     DS_Size data_size;
     DS_Size size;
};

BinaryTree BinaryTree_Create(DS_Size data_size)
{
    BinaryTree tree = (BinaryTree)malloc(sizeof (struct binary_tree));
    assert(tree);
    tree->root = NULL;
    tree->data_size = data_size;
    tree->size = 0;
    return tree;
}

DS_Void BinaryTree_Destroy(BinaryTree tree)
{
    free(tree);
}

DS_Void BinaryTree_InsertLeft(BinaryTree tree, BinaryTreeNode node, const DS_Generic data)
{
     node->left = BinaryTreeNode_Create(data, tree->data_size);
     tree->size++;
}

DS_Void BinaryTree_InsertRight(BinaryTree tree, BinaryTreeNode node, const DS_Generic data)
{
     node->right = BinaryTreeNode_Create(data, tree->data_size);
     tree->size++;
}

DS_Void BinaryTree_Remove(BinaryTree tree, BinaryTreeNode node)
{
     BinaryTreeNode nCurrent = node;
     if (node == node->parent->left) {
          node->parent->left = node->left;
     }
     if (node == node->parent->right) {

     }
     BinaryTreeNode_Destroy(node);
}