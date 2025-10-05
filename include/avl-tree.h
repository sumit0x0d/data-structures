#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <data-structures.h>

typedef struct AvlTreeNode * AvlTreeNode;
typedef struct AvlTree * AvlTree;

DATA_STRUCTURES_API
AvlTree AvlTree_Create(
     DS_Size            data_size,
     DS_CallbackCompare compare_callback,
     DS_Generic         compare_context
);

DATA_STRUCTURES_API
DS_Void AvlTree_Destroy(
     AvlTree avl_tree
);

DATA_STRUCTURES_API
DS_Size AvlTree_GetSize(
     AvlTree avl_tree
);

DATA_STRUCTURES_API
DS_Size AvlTree_GetDataSize(
     AvlTree avl_tree
);

DATA_STRUCTURES_API
DS_Generic AvlTree_GetNodeData(
     AvlTreeNode node
);

DATA_STRUCTURES_API
AvlTreeNode AvlTree_Search(
     AvlTree          avl_tree,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void AvlTree_Insert(
     AvlTree          avl_tree,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void AvlTree_Remove(
     AvlTree          avl_tree,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void AvlTree_TraversePreorder(
     AvlTree          avl_tree,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
);

DATA_STRUCTURES_API
DS_Void AvlTree_TraverseInorder(
     AvlTree          avl_tree,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
);

DATA_STRUCTURES_API
DS_Void AvlTree_TraversePostorder(
     AvlTree          avl_tree,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
);

DATA_STRUCTURES_API
DS_Void AvlTree_TraverseLevelorder(
     AvlTree          avl_tree,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
);

#endif