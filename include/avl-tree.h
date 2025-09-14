#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <data-structures.h>

typedef struct avl_tree_node * AvlTreeNode;
typedef struct avl_tree * AvlTree;

DS_PUBLIC_API
AvlTree AvlTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Context cCompare);

DS_PUBLIC_API
void AvlTree_Destroy(AvlTree tree);

DS_PUBLIC_API
DS_Size AvlTree_GetSize(AvlTree tree);

DS_PUBLIC_API
DS_Size AvlTree_GetDataSize(AvlTree tree);

DS_PUBLIC_API
DS_Data AvlTreeNode_GetData(AvlTreeNode node);

DS_PUBLIC_API
AvlTreeNode AvlTree_Search(AvlTree tree, const DS_Data data);

DS_PUBLIC_API
void AvlTree_Insert(AvlTree tree, const DS_Data data);

DS_PUBLIC_API
void AvlTree_Remove(AvlTree tree, const DS_Data data);

DS_PUBLIC_API
void AvlTree_TraversePreorder(AvlTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void AvlTree_TraverseInorder(AvlTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void AvlTree_TraversePostorder(AvlTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void AvlTree_TraverseLevelorder(AvlTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

#endif