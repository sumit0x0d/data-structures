#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <data-structures.h>

typedef struct binary_tree BinaryTree;
typedef struct binary_tree_node BinaryTreeNode;

DS_PUBLIC_API
BinaryTree *BinaryTree_create(DS_Size size);

DS_PUBLIC_API
void BinaryTree_destroy(BinaryTree *btree);

DS_PUBLIC_API
void BinaryTree_insert_left(BinaryTree *btree, BinaryTreeNode *node, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_insert_right(BinaryTree *btree, BinaryTreeNode *node, const DS_Data data);

DS_PUBLIC_API
BinaryTreeNode *BinaryTree_search(BinaryTree *btree, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_remove(BinaryTree *btree, const DS_Data data);

DS_PUBLIC_API
void BinaryTree_traverse_preorder(BinaryTree *btree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_traverse_inorder(BinaryTree *btree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_traverse_postorder(BinaryTree *btree, void (*traverse)(DS_Data data));

DS_PUBLIC_API
void BinaryTree_traverse_levelorder(BinaryTree *btree, void (*traverse)(DS_Data data));

#endif
