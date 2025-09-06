#ifndef DATA_STRUCTURES_AVL_TREE_NODE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_H

#include <avl-tree.h>
#include <circular-buffer.h>

struct avl_tree_node {
    DS_Data data;
    AvlTreeNode *parent;
    AvlTreeNode *left;
    AvlTreeNode *right;
    DS_UInt8 balance_factor;
};

DS_PRIVATE_API
AvlTreeNode *DS_AvlTreeNode_Create(const DS_Data data, DS_Size sData);

DS_PRIVATE_API
void DS_AvlTreeNode_Destroy(AvlTreeNode *node);

DS_PRIVATE_API
DS_Size DS_AvlTreeNode_GetHeight(AvlTreeNode *node, CircularBuffer *cBuffer);

DS_PRIVATE_API
void DS_AvlTreeNode_UpdateBalanceFactor(AvlTreeNode *node, CircularBuffer *cBuffer);

DS_PRIVATE_API
AvlTreeNode *DS_AvlTreeNode_GetPredecessor(AvlTreeNode *node);

DS_PRIVATE_API
AvlTreeNode *DS_AvlTreeNode_GetSuccessor(AvlTreeNode *node);

#endif