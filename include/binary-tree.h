#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct BinaryTree * BinaryTree;
typedef struct BinaryTreeNode * BinaryTreeNode;

DATA_STRUCTURES_API
BinaryTree BinaryTree_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void BinaryTree_Destroy(BinaryTree this);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertLeft(BinaryTree this, BinaryTreeNode this_node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertRight(BinaryTree this, BinaryTreeNode this_node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_Remove(BinaryTree this, BinaryTreeNode this_nod);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePreorder(BinaryTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseInorder(BinaryTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePostorder(BinaryTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseLevelorder(BinaryTree this, DS_UnaryCallback unary_callback);

#endif
