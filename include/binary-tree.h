#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct binary_tree * BinaryTree;
typedef struct binary_tree_node * BinaryTreeNode;

DS_API
BinaryTree BinaryTree_Create(DS_Size sData);

DS_API
void BinaryTree_Destroy(BinaryTree tree);

DS_API
void BinaryTree_InsertLeft(BinaryTree tree, BinaryTreeNode node, const DS_Data data);

DS_API
void BinaryTree_InsertRight(BinaryTree tree, BinaryTreeNode node, const DS_Data data);

DS_API
void BinaryTree_Remove(BinaryTree tree, BinaryTreeNode node);

DS_API
void BinaryTree_TraversePreorder(BinaryTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
void BinaryTree_TraverseInorder(BinaryTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
void BinaryTree_TraversePostorder(BinaryTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
void BinaryTree_TraverseLevelorder(BinaryTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

#endif
