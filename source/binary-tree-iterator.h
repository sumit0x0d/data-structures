#ifndef DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H
#define DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H

#include <data-structures.h>

DS_Void GenericBinaryTree_TraversePreorder(DS_Generic node, DS_Size node_size,
                                           DS_Size binary_tree_size, DS_Size data_offeset,
                                           DS_Size left_offset, DS_Size right_offset,
                                           DS_UnaryCallback unary_callback);

DS_Void GenericBinaryTree_TraverseInorder(DS_Generic node, DS_Size node_size,
                                          DS_Size binary_tree_size, DS_Size data_offeset,
                                          DS_Size left_offset, DS_Size right_offset,
                                          DS_CallbackUnary unary_callback.function,
                                          DS_Generic unary_callback.context);

DS_Void GenericBinaryTree_TraversePostorder(DS_Generic node, DS_Size node_size,
                                            DS_Size binary_tree_size, DS_Size data_offeset,
                                            DS_Size left_offset, DS_Size right_offset,
                                            DS_CallbackUnary unary_callback.function,
                                            DS_Generic unary_callback.context);

DS_Void GenericBinaryTree_TraverseLevelorder(DS_Generic node, DS_Size node_size,
                                             DS_Size binary_tree_size, DS_Size data_offeset,
                                             DS_Size left_offset, DS_Size right_offset,
                                             DS_CallbackUnary unary_callback.function,
                                             DS_Generic unary_callback.context);

#endif