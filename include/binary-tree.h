#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct BinaryTree * BinaryTree;
typedef struct BinaryTreeNode * BinaryTreeNode;

DATA_STRUCTURES_API
BinaryTree BinaryTree_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void BinaryTree_Destroy(BinaryTree self);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertLeft(BinaryTree self, BinaryTreeNode self_node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertRight(BinaryTree self, BinaryTreeNode self_node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_Remove(BinaryTree self, BinaryTreeNode self_nod);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePreorder(BinaryTree self, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseInorder(BinaryTree self, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePostorder(BinaryTree self, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseLevelorder(BinaryTree self, DS_UnaryCallback unary_callback);

#endif
