#ifndef DATA_STRUCTURES_BINARY_TREE_NODE_H
#define DATA_STRUCTURES_BINARY_TREE_NODE_H

#include <binary-tree.h>
#include <stack.h>

struct BinaryTreeNode {
     DS_Generic data;
     BinaryTreeNode parent;
     BinaryTreeNode left;
     BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(const DS_Generic data, DS_Size data_size);

DS_Void BinaryTreeNode_Destroy(BinaryTreeNode node);

#endif