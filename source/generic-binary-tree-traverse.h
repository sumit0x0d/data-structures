#ifndef DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H
#define DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H

#include <data-structures.h>


void GenericBinaryTree_TraversePreorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                        DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                        DS_Context cUnary);

void GenericBinaryTree_TraverseInorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                       DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                       DS_Context cUnary);

void GenericBinaryTree_TraversePostorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                         DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                         DS_Context cUnary);

void GenericBinaryTree_TraverseLevelorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                          DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                          DS_Context cUnary);

#endif