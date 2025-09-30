#ifndef DATA_STRUCTURES_AVL_TREE_NODE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_H

#include <avl-tree.h>
#include <circular-buffer.h>

struct avl_tree_node {
    DS_Generic data;
    AvlTreeNode parent;
    AvlTreeNode left;
    AvlTreeNode right;
    DS_UInt8 balance_factor;
};


AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size);


DS_Void AvlTreeNode_Destroy(AvlTreeNode node);


DS_Size AvlTreeNode_GetHeight(AvlTreeNode node, CircularBuffer buffer);


DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode node, CircularBuffer buffer);


AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode node);


AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode node);

#endif