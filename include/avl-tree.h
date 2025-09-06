#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <data-structures.h>

typedef struct avl_tree_node AvlTreeNode;
typedef struct avl_tree AvlTree;

DS_PUBLIC_API
AvlTree *DS_AvlTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_AvlTree_Destroy(AvlTree *tree);

DS_PUBLIC_API
DS_Size DS_AvlTree_GetSize(AvlTree *tree);

DS_PUBLIC_API
DS_Size DS_AvlTree_GetDataSize(AvlTree *tree);

DS_PUBLIC_API
DS_Data AvlTreeNode_GetData(AvlTreeNode *node);

DS_PUBLIC_API
AvlTreeNode *DS_AvlTree_Search(AvlTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_AvlTree_Insert(AvlTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_AvlTree_Remove(AvlTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_AvlTree_TraversePreorder(AvlTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_AvlTree_TraverseInorder(AvlTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_AvlTree_TraversePostorder(AvlTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_AvlTree_TraverseLevelorder(AvlTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

#endif