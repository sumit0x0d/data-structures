#ifndef DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H
#define DATA_STRUCTURES_BINARY_TREE_TRAVERSE_H

#include <data-structures.h>

typedef struct {
    DS_Generic tree_root;
    DS_Offset left_offset;
    DS_Offset right_offset;
    DS_Offset data_offest;
    DS_Size node_size;
    DS_Size tree_size;
    DS_FunctionTraverse traverse_function;
    DS_Context traverse_context;
} GenericBinaryTreeTraverseInfo;

DS_PRIVATE_API
void GenericBinaryTree_TraversePreorder(GenericBinaryTreeTraverseInfo *bttInfo);

DS_PRIVATE_API
void GenericBinaryTree_TraverseInorder(GenericBinaryTreeTraverseInfo *bttInfo);

DS_PRIVATE_API
void GenericBinaryTree_TraversePostorder(GenericBinaryTreeTraverseInfo *bttInfo);

DS_PRIVATE_API
void GenericBinaryTree_TraverseLevelorder(GenericBinaryTreeTraverseInfo *bttInfo);

#endif