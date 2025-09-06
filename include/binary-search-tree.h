#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <data-structures.h>

typedef struct binary_search_tree BinarySearchTree;
typedef struct binary_search_tree_node BinarySearchTreeNode;

DS_PUBLIC_API
BinarySearchTree *DS_BinarySearchTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_BinarySearchTree_Destroy(BinarySearchTree *tree);

DS_PUBLIC_API
void DS_BinarySearchTree_Insert(BinarySearchTree *tree, const DS_Data data);

DS_PUBLIC_API
BinarySearchTreeNode *DS_BinarySearchTree_Search(BinarySearchTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_BinarySearchTree_Remove(BinarySearchTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_BinarySearchTree_TraversePreorder(BinarySearchTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_BinarySearchTree_TraverseInorder(BinarySearchTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_BinarySearchTree_TraversePostorder(BinarySearchTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

DS_PUBLIC_API
void DS_BinarySearchTree_TraverseLevelorder(BinarySearchTree *tree, DS_FunctionTraverse fTraverse, DS_Data dUser);

#endif
