#ifndef DATA_STRUCTURES_AVL_TREE_NODE_H
#define DATA_STRUCTURES_AVL_TREE_NODE_H

#include <avl-tree.h>

typedef enum {
     AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY_2 = -2,
     AVL_TREE_NODE_BALANCE_FACTOR_LEFT_HEAVY_1 = -1,
     AVL_TREE_NODE_BALANCE_FACTOR_BALANCED = 0,
     AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY_1 = +1,
     AVL_TREE_NODE_BALANCE_FACTOR_RIGHT_HEAVY_2 = +2
} AvlTreeNodeBalanceFactor;

struct AvlTreeNode {
     DS_Generic data;
     AvlTreeNode parent;
     AvlTreeNode left;
     AvlTreeNode right;
     DS_Size height;
     AvlTreeNodeBalanceFactor balance_factor;
};

AvlTreeNode AvlTreeNode_Create(const DS_Generic data, DS_Size data_size);
DS_Void AvlTreeNode_Destroy(AvlTreeNode this);

DS_Void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode this, DS_Size queue_capacity);
AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode this);
AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode this);

#endif