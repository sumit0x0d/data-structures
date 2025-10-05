#include <stdlib.h>

#include <binary-tree-node.h>

struct BinaryTreeNode {
     DS_Generic     data;
     BinaryTreeNode parent;
     BinaryTreeNode left;
     BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(
     const DS_Generic data,
     DS_Size data_size
) {
     BinaryTreeNode node = (BinaryTreeNode)malloc(sizeof (BinaryTreeNode));
     if (!node) {
          return NULL;
     } 
     node->data = malloc(data_size);
     if (!node->data) {
          free(node);
          return NULL;
     }
     memcpy(node->data, data, data_size);
     node->left = NULL;
     node->right = NULL;
     return node;
}

DS_Void BinaryTreeNode_Destroy(
     BinaryTreeNode node
) {
     free(node->data);
     free(node);
}