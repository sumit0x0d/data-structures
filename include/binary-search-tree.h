#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H



typedef struct BinarySearchTree * BinarySearchTree;
typedef struct BinarySearchTreeNode * BinarySearchTreeNode;

__attribute__((visibility("default")))
BinarySearchTree BinarySearchTree_Create(size_t data_size, DS_CompareCallback compare_callback);

__attribute__((visibility("default")))
void BinarySearchTree_Destroy(BinarySearchTree this);

__attribute__((visibility("default")))
void BinarySearchTree_Insert(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
void BinarySearchTree_Remove(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
void BinarySearchTree_TraversePreorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraverseInorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraversePostorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraverseLevelorder(BinarySearchTree this, DS_UnaryCallback unary_callback);

#endif
