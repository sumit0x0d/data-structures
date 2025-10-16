#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

#include <red-black-tree.h>

typedef enum RedBlackTreeNodeColor {
     RED_BLACK_TREE_NODE_COLOR_RED = 0,
     RED_BLACK_TREE_NODE_COLOR_BLACK = 1
} RedBlackTreeNodeColor;

struct RedBlackTreeNode {
     DS_Generic data;
     RedBlackTreeNode parent;
     RedBlackTreeNode left;
     RedBlackTreeNode right;
     RedBlackTreeNodeColor color;
};

RedBlackTreeNode RedBlackTreeNode_Create(
     const DS_Generic data,
     DS_Size data_size
);

DS_Void RedBlackTreeNode_Destroy(
     RedBlackTreeNode node
);

#endif