#ifndef DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H
#define DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H

#include <data-structures.h>


DS_Void GenericBinaryTree_TraversePreorder(DS_Generic node_generic, DS_Size node_size, DS_Size tree_size,
                                           DS_Offset data_offeset, DS_Offset left_offset, DS_Offset right_offset,
                                           DS_FunctionUnary unary_function, DS_Context unary_context);

DS_Void GenericBinaryTree_TraverseInorder(DS_Generic node_generic, DS_Size node_size, DS_Size tree_size,
                                          DS_Offset data_offeset, DS_Offset left_offset, DS_Offset right_offset,
                                          DS_FunctionUnary unary_function, DS_Context unary_context);

DS_Void GenericBinaryTree_TraversePostorder(DS_Generic node_generic, DS_Size node_size, DS_Size tree_size,
                                            DS_Offset data_offeset, DS_Offset left_offset, DS_Offset right_offset,
                                            DS_FunctionUnary unary_function, DS_Context unary_context);

DS_Void GenericBinaryTree_TraverseLevelorder(DS_Generic node_generic, DS_Size node_size, DS_Size tree_size,
                                             DS_Offset data_offeset, DS_Offset left_offset, DS_Offset right_offset,
                                             DS_FunctionUnary unary_function, DS_Context unary_context);

#endif