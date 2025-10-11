#include <assert.h>
#include <stdlib.h>

#include <binary-tree-node.h>

struct BinaryTree {
     BinaryTreeNode root;
     DS_Size        data_size;
     DS_Size        size;
};

BinaryTree BinaryTree_Create(
     DS_Size data_size
) {
     BinaryTree binary_tree;

     binary_tree = (BinaryTree)malloc(sizeof (struct BinaryTree));
     if (!binary_tree) {
          return NULL;
     }

     binary_tree->root = NULL;
     binary_tree->data_size = data_size;
     binary_tree->size = 0;
     
     return binary_tree;
}

DS_Void BinaryTree_Destroy(
     BinaryTree tree
) {
     free(tree);
}

DS_Void BinaryTree_InsertLeft(
     BinaryTree       binary_tree,
     BinaryTreeNode   node,
     const DS_Generic data
) {
     node->left = BinaryTreeNode_Create(data, binary_tree->data_size);
     binary_tree->size++;
}

DS_Void BinaryTree_InsertRight(
     BinaryTree       binary_tree,
     BinaryTreeNode   node,
     const DS_Generic data
) {
     node->right = BinaryTreeNode_Create(data, binary_tree->data_size);
     binary_tree->size++;
}

DS_Void BinaryTree_Remove(
     BinaryTree     binary_tree,
     BinaryTreeNode node
) {
     if (node == node->parent->left) {
          node->parent->left = node->left;
     }
     
     if (node == node->parent->right) {

     }
     
     BinaryTreeNode_Destroy(node);
}