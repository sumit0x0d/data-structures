#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <data-structures.h>

typedef struct BinarySearchTree * BinarySearchTree;
typedef struct BinarySearchTreeNode * BinarySearchTreeNode;

DATA_STRUCTURES_API
BinarySearchTree BinarySearchTree_Create(DS_Size data_size, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_Destroy(BinarySearchTree this);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_Insert(BinarySearchTree this, const DS_Generic data);

DATA_STRUCTURES_API
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_Remove(BinarySearchTree this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_TraversePreorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_TraverseInorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_TraversePostorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void BinarySearchTree_TraverseLevelorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

#endif
