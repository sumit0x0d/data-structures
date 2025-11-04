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
     void *data;
     AvlTreeNode parent;
     AvlTreeNode left;
     AvlTreeNode right;
     size_t height;
     AvlTreeNodeBalanceFactor balance_factor;
};

AvlTreeNode AvlTreeNode_Create(const void *data, size_t data_size);
void AvlTreeNode_Destroy(AvlTreeNode this);

void AvlTreeNode_UpdateBalanceFactor(AvlTreeNode this, size_t queue_capacity);
AvlTreeNode AvlTreeNode_GetPredecessor(AvlTreeNode this);
AvlTreeNode AvlTreeNode_GetSuccessor(AvlTreeNode this);

#endif