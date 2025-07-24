#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct red_black_tree RedBlackTree;
typedef struct red_black_tree_node RedBlackTreeNode;
typedef int (*RedBlackTreeCompare)(const void *data1, const void *data2, void *uData);

RedBlackTree *RedBlackTree_Create(size_t dSize, RedBlackTreeCompare rbtCompare, void *uData);
void RedBlackTree_Destroy(RedBlackTree *rbTree);

size_t RedBlackTree_GetSize(RedBlackTree *rbTree);
void *RedBlackTreeNode_GetData(RedBlackTreeNode *rbtNode);

void RedBlackTree_Insert(RedBlackTree *rbTree, const void *data);
RedBlackTreeNode *RedBlackTree_Search(RedBlackTree *rbTree, const void *data);
void RedBlackTree_Remove(RedBlackTree *rbTree, const void *data);

#endif
