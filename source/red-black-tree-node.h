#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

#include <red-black-tree.h>

typedef enum red_black_tree_node_color {
    RED_BLACK_TREE_NODE_COLOR_RED = 0,
    RED_BLACK_TREE_NODE_COLOR_BLACK = 1
} RedBlackTreeNodeColor;

struct red_black_tree_node {
    DS_Data data;
    RedBlackTreeNode *parent;
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;
    RedBlackTreeNodeColor color;
};

DS_PRIVATE_API
RedBlackTreeNode *RedBlackTreeNode_Create(const DS_Data data, DS_Size sData);

DS_PRIVATE_API
void RedBlackTreeNode_Destroy(RedBlackTreeNode *node);

#endif