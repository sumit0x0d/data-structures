#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

typedef struct BinarySearchTree * BinarySearchTree;
typedef struct BinarySearchTreeNode * BinarySearchTreeNode;

typedef enum {
     BINARY_SEARCH_TREE_COMPARE_LESS = -1,
     BINARY_SEARCH_TREE_COMPARE_EQUAL = 0,
     BINARY_SEARCH_TREE_COMPARE_GREATER = 1
} BinarySearchTreeCompare;

typedef struct {
     BinarySearchTreeCompare (*function)(const void *data1, const void *data2, void *user_data);
     void *user_data;
} BinarySearchTreeCompareCallback;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} BinarySearchTreeUnaryCallback;

__attribute__((visibility("default")))
BinarySearchTree BinarySearchTree_Create(size_t data_size, BinarySearchTreeCompareCallback compare_callback);

__attribute__((visibility("default")))
void BinarySearchTree_Destroy(BinarySearchTree this);

__attribute__((visibility("default")))
void BinarySearchTree_Insert(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
void BinarySearchTree_Remove(BinarySearchTree this, const void *data);

__attribute__((visibility("default")))
void BinarySearchTree_TraversePreorder(BinarySearchTree this, BinarySearchTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraverseInorder(BinarySearchTree this, BinarySearchTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraversePostorder(BinarySearchTree this, BinarySearchTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinarySearchTree_TraverseLevelorder(BinarySearchTree this, BinarySearchTreeUnaryCallback unary_callback);

#endif