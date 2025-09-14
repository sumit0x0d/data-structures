#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <data-structures.h>

typedef struct binary_search_tree * BinarySearchTree;
typedef struct binary_search_tree_node * BinarySearchTreeNode;

DS_PUBLIC_API
BinarySearchTree BinarySearchTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Context cCompare);

DS_PUBLIC_API
void BinarySearchTree_Destroy(BinarySearchTree tree);

DS_PUBLIC_API
void BinarySearchTree_Insert(BinarySearchTree tree, const DS_Data data);

DS_PUBLIC_API
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree tree, const DS_Data data);

DS_PUBLIC_API
void BinarySearchTree_Remove(BinarySearchTree tree, const DS_Data data);

DS_PUBLIC_API
void BinarySearchTree_TraversePreorder(BinarySearchTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void BinarySearchTree_TraverseInorder(BinarySearchTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void BinarySearchTree_TraversePostorder(BinarySearchTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

DS_PUBLIC_API
void BinarySearchTree_TraverseLevelorder(BinarySearchTree tree, DS_FunctionTraverse fTraverse, DS_Context cTraverse);

#endif
