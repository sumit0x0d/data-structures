#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct BinaryTree * BinaryTree;
typedef struct BinaryTreeNode * BinaryTreeNode;

DATA_STRUCTURES_API
BinaryTree BinaryTree_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void BinaryTree_Destroy(BinaryTree binary_tree);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertLeft(BinaryTree binary_tree,
                              BinaryTreeNode binary_tree_node,
                              const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_InsertRight(BinaryTree binary_tree,
                               BinaryTreeNode binary_tree_node,
                               const DS_Generic data);

DATA_STRUCTURES_API
DS_Void BinaryTree_Remove(BinaryTree binary_tree, BinaryTreeNode binary_tree_nod);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePreorder(BinaryTree binary_tree,
                                    DS_CallbackUnary unary_callback,
                                    DS_Generic unary_context);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseInorder(BinaryTree binary_tree,
                                   DS_CallbackUnary unary_callback,
                                   DS_Generic unary_context);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraversePostorder(BinaryTree binary_tree,
                                     DS_CallbackUnary unary_callback,
                                     DS_Generic unary_context);

DATA_STRUCTURES_API
DS_Void BinaryTree_TraverseLevelorder(BinaryTree binary_tree,
                                      DS_CallbackUnary unary_callback,
                                      DS_Generic unary_context);

#endif
