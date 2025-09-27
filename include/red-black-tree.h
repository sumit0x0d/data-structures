#ifndef DATA_STRUCTURES_RED_BLACK_TREE_H
#define DATA_STRUCTURES_RED_BLACK_TREE_H

#include <data-structures.h>

typedef struct red_black_tree * RedBlackTree;
typedef struct red_black_tree_node * RedBlackTreeNode;

DS_API
RedBlackTree RedBlackTree_Create(DS_Size data_size, DS_FunctionCompare compare_function, DS_Context compare_context);

DS_API
DS_Void RedBlackTree_Destroy(RedBlackTree tree);

DS_API
DS_Size RedBlackTree_GetSize(RedBlackTree tree);

DS_API
DS_Data RedBlackTree_GetNodeData(RedBlackTreeNode node);

DS_API
DS_Void RedBlackTree_Insert(RedBlackTree tree, const DS_Data data);

DS_API
RedBlackTreeNode RedBlackTree_Search(RedBlackTree tree, const DS_Data data);

DS_API
DS_Void RedBlackTree_Remove(RedBlackTree tree, const DS_Data data);

#endif
