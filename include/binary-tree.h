#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct binary_tree * BinaryTree;
typedef struct binary_tree_node * BinaryTreeNode;

DS_API
BinaryTree BinaryTree_Create(DS_Size data_size);

DS_API
DS_Void BinaryTree_Destroy(BinaryTree tree);

DS_API
DS_Void BinaryTree_InsertLeft(BinaryTree tree, BinaryTreeNode node, const DS_Data data);

DS_API
DS_Void BinaryTree_InsertRight(BinaryTree tree, BinaryTreeNode node, const DS_Data data);

DS_API
DS_Void BinaryTree_Remove(BinaryTree tree, BinaryTreeNode node);

DS_API
DS_Void BinaryTree_TraversePreorder(BinaryTree tree, DS_FunctionUnary unary_function, DS_Context unary_context);

DS_API
DS_Void BinaryTree_TraverseInorder(BinaryTree tree, DS_FunctionUnary unary_function, DS_Context unary_context);

DS_API
DS_Void BinaryTree_TraversePostorder(BinaryTree tree, DS_FunctionUnary unary_function, DS_Context unary_context);

DS_API
DS_Void BinaryTree_TraverseLevelorder(BinaryTree tree, DS_FunctionUnary unary_function, DS_Context unary_context);

#endif
