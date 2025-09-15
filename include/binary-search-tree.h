#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <data-structures.h>

typedef struct binary_search_tree * BinarySearchTree;
typedef struct binary_search_tree_node * BinarySearchTreeNode;

DS_API
BinarySearchTree BinarySearchTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Context cCompare);

DS_API
DS_Void BinarySearchTree_Destroy(BinarySearchTree tree);

DS_API
DS_Void BinarySearchTree_Insert(BinarySearchTree tree, const DS_Data data);

DS_API
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree tree, const DS_Data data);

DS_API
DS_Void BinarySearchTree_Remove(BinarySearchTree tree, const DS_Data data);

DS_API
DS_Void BinarySearchTree_TraversePreorder(BinarySearchTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
DS_Void BinarySearchTree_TraverseInorder(BinarySearchTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
DS_Void BinarySearchTree_TraversePostorder(BinarySearchTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

DS_API
DS_Void BinarySearchTree_TraverseLevelorder(BinarySearchTree tree, DS_FunctionUnary fUnary, DS_Context cUnary);

#endif
