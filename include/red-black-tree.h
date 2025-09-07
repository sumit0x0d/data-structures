#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <data-structures.h>

typedef struct red_black_tree RedBlackTree;
typedef struct red_black_tree_node RedBlackTreeNode;

DS_PUBLIC_API
RedBlackTree *RedBlackTree_Create(DS_Size size, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void RedBlackTree_Destroy(RedBlackTree *tree);

DS_PUBLIC_API
DS_Size RedBlackTree_GetSize(RedBlackTree *tree);

DS_PUBLIC_API
void *RedBlackTreeNode_GetData(RedBlackTreeNode *node);

DS_PUBLIC_API
void RedBlackTree_Insert(RedBlackTree *tree, const DS_Data data);

DS_PUBLIC_API
RedBlackTreeNode *RedBlackTree_Search(RedBlackTree *tree, const DS_Data data);

DS_PUBLIC_API
void RedBlackTree_Remove(RedBlackTree *tree, const DS_Data data);

#endif
