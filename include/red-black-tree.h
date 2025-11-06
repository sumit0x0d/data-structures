#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <stddef.h>

typedef struct RedBlackTree RedBlackTree;
typedef struct RedBlackTreeNode RedBlackTreeNode;

typedef enum RedBlackTreeCompare {
     RED_BLACK_TREE_COMPARE_LESS = -1,
     RED_BLACK_TREE_COMPARE_EQUAL = 0,
     RED_BLACK_TREE_COMPARE_GREATER = 1
} RedBlackTreeCompare;

typedef struct RedBlackTreeCompareCallback {
     RedBlackTreeCompare (*function)(const void *data1, const void *data2, void *user_data);
     void *user_data;
} RedBlackTreeCompareCallback;

__attribute__((visibility("default")))
RedBlackTree *RedBlackTree_Create(size_t data_size, RedBlackTreeCompareCallback compare_callback);

__attribute__((visibility("default")))
void RedBlackTree_Destroy(RedBlackTree *this);

__attribute__((visibility("default")))
size_t RedBlackTree_GetSize(RedBlackTree *this);

__attribute__((visibility("default")))
void *RedBlackTree_GetNodeData(RedBlackTreeNode *node);

__attribute__((visibility("default")))
void RedBlackTree_Insert(RedBlackTree *this, const void *data);

__attribute__((visibility("default")))
RedBlackTreeNode *RedBlackTree_Search(RedBlackTree *this, const void *data);

__attribute__((visibility("default")))
void RedBlackTree_Remove(RedBlackTree *this, const void *data);

#endif
