#ifndef DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H
#define DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H



void GenericBinaryTree_TraversePreorder(void *node, size_t node_size, size_t binary_tree_size,
     size_t data_offeset, size_t left_offset, size_t right_offset, DS_UnaryCallback unary_callback);

void GenericBinaryTree_TraverseInorder(void *node, size_t node_size, size_t binary_tree_size,
     size_t data_offeset, size_t left_offset, size_t right_offset, DS_UnaryCallback unary_callback);

void GenericBinaryTree_TraversePostorder(void *node, size_t node_size, size_t binary_tree_size,
     size_t data_offeset, size_t left_offset, size_t right_offset, DS_UnaryCallback unary_callback);

void GenericBinaryTree_TraverseLevelorder(void *node, size_t node_size, size_t binary_tree_size,
     size_t data_offeset, size_t left_offset, size_t right_offset, DS_UnaryCallback unary_callback);

#endif