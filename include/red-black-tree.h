#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <data-structures.h>

typedef struct RedBlackTree * RedBlackTree;
typedef struct RedBlackTreeNode * RedBlackTreeNode;

DATA_STRUCTURES_API
RedBlackTree RedBlackTree_Create(DS_Size data_size, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void RedBlackTree_Destroy(RedBlackTree self);

DATA_STRUCTURES_API
DS_Size RedBlackTree_GetSize(RedBlackTree self);

DATA_STRUCTURES_API
DS_Generic RedBlackTree_GetNodeData(RedBlackTreeNode node);

DATA_STRUCTURES_API
DS_Void RedBlackTree_Insert(RedBlackTree self, const DS_Generic data);

DATA_STRUCTURES_API
RedBlackTreeNode RedBlackTree_Search(RedBlackTree self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void RedBlackTree_Remove(RedBlackTree self, const DS_Generic data);

#endif
