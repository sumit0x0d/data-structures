#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <data-structures.h>

typedef struct red_black_tree RedBlackTree;
typedef struct red_black_tree_node RedBlackTreeNode;

DS_PUBLIC_API
RedBlackTree *DS_RedBlackTree_Create(DS_Size size, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_RedBlackTree_Destroy(RedBlackTree *tree);

DS_PUBLIC_API
DS_Size DS_RedBlackTree_GetSize(RedBlackTree *tree);

DS_PUBLIC_API
void *RedBlackTreeNode_GetData(RedBlackTreeNode *node);

DS_PUBLIC_API
void DS_RedBlackTree_Insert(RedBlackTree *tree, const DS_Data data);

DS_PUBLIC_API
RedBlackTreeNode *DS_RedBlackTree_Search(RedBlackTree *tree, const DS_Data data);

DS_PUBLIC_API
void DS_RedBlackTree_Remove(RedBlackTree *tree, const DS_Data data);

#endif
