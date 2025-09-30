#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <data-structures.h>

typedef struct avl_tree_node * AvlTreeNode;
typedef struct avl_tree * AvlTree;

DS_API
AvlTree AvlTree_Create(DS_Size data_size, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void AvlTree_Destroy(AvlTree tree);

DS_API
DS_Size AvlTree_GetSize(AvlTree tree);

DS_API
DS_Size AvlTree_GetDataSize(AvlTree tree);

DS_API
DS_Generic AvlTree_GetNodeData(AvlTreeNode node);

DS_API
AvlTreeNode AvlTree_Search(AvlTree tree, const DS_Generic data);

DS_API
DS_Void AvlTree_Insert(AvlTree tree, const DS_Generic data);

DS_API
DS_Void AvlTree_Remove(AvlTree tree, const DS_Generic data);

DS_API
DS_Void AvlTree_TraversePreorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void AvlTree_TraverseInorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void AvlTree_TraversePostorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void AvlTree_TraverseLevelorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context);

#endif