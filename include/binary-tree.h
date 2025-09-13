#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct binary_tree * BinaryTree;
typedef struct binary_tree_node * BinaryTreeNode;

DS_PUBLIC_API
BinaryTree BinaryTree_Create(DS_Size size);

DS_PUBLIC_API
void BinaryTree_Destroy(BinaryTree tree);

DS_PUBLIC_API
void BinaryTree_InsertLeft(BinaryTree tree, BinaryTreeNode *node, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_InsertRight(BinaryTree tree, BinaryTreeNode *node, const DS_Data data);

DS_PUBLIC_API
BinaryTreeNode *BinaryTree_Search(BinaryTree tree, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_Remove(BinaryTree tree, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_TraversePreorder(BinaryTree tree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_TraverseInorder(BinaryTree tree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_TraversePostorder(BinaryTree tree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_TraverseLevelorder(BinaryTree tree, void (*traverse)(DS_Data data));

#endif
