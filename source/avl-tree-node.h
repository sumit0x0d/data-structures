#ifndef DATA_STRUCTURES_AVL_TREE_NODE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_H

#include <avl-tree.h>
#include <circular-buffer.h>

typedef enum {
     AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY = -2,
     AVL_TREE_NODE_BALANCE_FACTOR_BALANCED = 0,
     AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY = +2
} AvlTreeNodeBalanceFactor;

struct AvlTreeNode {
     DS_Generic data;
     AvlTreeNode parent;
     AvlTreeNode left;
     AvlTreeNode right;
     DS_Int8 balance_factor;
};

AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size);

DS_Void AvlTreeNode_Destroy(AvlTreeNode self);

DS_Size AvlTreeNode_GetHeight(AvlTreeNode self, CircularBuffer circular_buffer);

DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode self, CircularBuffer circular_buffer);

AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode self);

AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode self);

#endif