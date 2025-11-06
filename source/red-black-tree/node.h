#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

#include <red-black-tree.h>

typedef enum RedBlackTreeNodeColor {
     RED_BLACK_TREE_NODE_COLOR_RED   = 1,
     RED_BLACK_TREE_NODE_COLOR_BLACK = 2
} RedBlackTreeNodeColor;

struct RedBlackTreeNode {
     void *data;
     RedBlackTreeNode *parent;
     RedBlackTreeNode *left;
     RedBlackTreeNode *right;
     RedBlackTreeNodeColor color;
};

RedBlackTreeNode *RedBlackTreeNode_Create(const void *data, size_t data_size);

void RedBlackTreeNode_Destroy(RedBlackTreeNode *this);

#endif