#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <data-structures.h>

typedef struct BinarySearchTree * BinarySearchTree;
typedef struct BinarySearchTreeNode * BinarySearchTreeNode;

DS_API
BinarySearchTree BinarySearchTree_Create(DS_Size data_size,
                    DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void BinarySearchTree_Destroy(BinarySearchTree binary_search_tree);

DS_API
DS_Void BinarySearchTree_Insert(BinarySearchTree binary_search_tree,
          const DS_Generic data);

DS_API
BinarySearchTreeNode BinarySearchTree_Search(BinarySearchTree binary_search_tree,
                         const DS_Generic data);

DS_API
DS_Void BinarySearchTree_Remove(BinarySearchTree binary_search_tree,
          const DS_Generic data);

DS_API
DS_Void BinarySearchTree_TraversePreorder(BinarySearchTree binary_search_tree,
          DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void BinarySearchTree_TraverseInorder(BinarySearchTree binary_search_tree,
          DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void BinarySearchTree_TraversePostorder(BinarySearchTree binary_search_tree,
          DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Void BinarySearchTree_TraverseLevelorder(BinarySearchTree binary_search_tree,
          DS_CallbackUnary unary_callback, DS_Generic unary_context);

#endif
