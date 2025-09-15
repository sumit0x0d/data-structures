#ifndef DATA_STRUCTURES_BINARY_TREE_NODE_H
#define DATA_STRUCTURES_BINARY_TREE_NODE_H

#include <binary-tree.h>
#include <stack.h>

struct binary_tree_node {
    DS_Data data;
    BinaryTreeNode parent;
    BinaryTreeNode left;
    BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(const DS_Data data, DS_Size sData);

DS_Void BinaryTreeNode_Destroy(BinaryTreeNode node);

#endif