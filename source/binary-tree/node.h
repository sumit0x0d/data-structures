#ifndef DATA_STRUCTURES_BINARY_TREE_NODE_H
#define DATA_STRUCTURES_BINARY_TREE_NODE_H

#include <binary-tree.h>
#include <stack.h>

struct BinaryTreeNode {
     void *data;
     BinaryTreeNode parent;
     BinaryTreeNode left;
     BinaryTreeNode right;
};

BinaryTreeNode BinaryTreeNode_Create(const void *data, size_t data_size);

void BinaryTreeNode_Destroy(BinaryTreeNode this);

#endif