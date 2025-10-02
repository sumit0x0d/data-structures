#ifndef DATA_STRUCTURES_AVL_TREE_NODE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_H

#include <avl-tree.h>
#include <circular-buffer.h>

struct AvlTreeNode {
    DS_Generic data;
    AvlTreeNode parent;
    AvlTreeNode left;
    AvlTreeNode right;
    DS_Int8 balance_factor;
};

AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size);

DS_Void AvlTreeNode_Destroy(AvlTreeNode avl_tree_node);

DS_Size AvlTreeNode_GetHeight(AvlTreeNode avl_tree_node, CircularBuffer circular_buffer);

DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode avl_tree_node,
    CircularBuffer circular_buffer);

AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode avl_tree_node);

AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode avl_tree_node);

#endif