#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include "stddef.h"

typedef struct AvlTree AvlTree;
typedef struct AvlTreeNode AvlTreeNode;

typedef enum {
     AVL_TREE_COMPARE_LESS = -1,
     AVL_TREE_COMPARE_EQUAL = 0,
     AVL_TREE_COMPARE_GREATER = 1
} AvlTreeCompare;

typedef struct {
     AvlTreeCompare (*function)(const void *data1, const void *data2, void *user_data);
     void *user_data;
} AvlTreeCompareCallback;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} AvlTreeUnaryCallback;

__attribute__((visibility("default")))
AvlTree *AvlTree_Create(size_t data_size, AvlTreeCompareCallback compare_callback);

__attribute__((visibility("default")))
void AvlTree_Destroy(AvlTree *this);

__attribute__((visibility("default")))
size_t AvlTree_GetSize(AvlTree *this);

__attribute__((visibility("default")))
size_t AvlTree_GetDataSize(AvlTree *this);

__attribute__((visibility("default")))
void *AvlTree_GetNodeData(AvlTreeNode *node);

__attribute__((visibility("default")))
AvlTreeNode *AvlTree_Search(AvlTree *this, const void *data);

__attribute__((visibility("default")))
void AvlTree_Insert(AvlTree *this, const void *data);

__attribute__((visibility("default")))
void AvlTree_Remove(AvlTree *this, const void *data);

__attribute__((visibility("default")))
void AvlTree_TraversePreorder(AvlTree *this, AvlTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void AvlTree_TraverseInorder(AvlTree *this, AvlTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void AvlTree_TraversePostorder(AvlTree *this, AvlTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void AvlTree_TraverseLevelorder(AvlTree *this, AvlTreeUnaryCallback unary_callback);

#endif