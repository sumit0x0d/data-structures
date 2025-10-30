#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <data-structures.h>

typedef struct AvlTree * AvlTree;
typedef struct AvlTreeNode * AvlTreeNode;

DATA_STRUCTURES_API
AvlTree AvlTree_Create(DS_Size data_size, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void AvlTree_Destroy(AvlTree this);

DATA_STRUCTURES_API
DS_Size AvlTree_GetSize(AvlTree this);

DATA_STRUCTURES_API
DS_Size AvlTree_GetDataSize(AvlTree this);

DATA_STRUCTURES_API
DS_Generic AvlTree_GetNodeData(AvlTreeNode node);

DATA_STRUCTURES_API
AvlTreeNode AvlTree_Search(AvlTree this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void AvlTree_Insert(AvlTree this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void AvlTree_Remove(AvlTree this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void AvlTree_TraversePreorder(AvlTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void AvlTree_TraverseInorder(AvlTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void AvlTree_TraversePostorder(AvlTree this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Void AvlTree_TraverseLevelorder(AvlTree this, DS_UnaryCallback unary_callback);

#endif