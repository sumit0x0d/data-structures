#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct binary_tree BinaryTree;
typedef struct binary_tree_node BinaryTreeNode;

BinaryTree *binary_tree_create(size_t dsize);
void binary_tree_destroy(BinaryTree *btree);

void binary_tree_insert_left(BinaryTree *btree, BinaryTreeNode *node, const void *data);
void binary_tree_insert_right(BinaryTree *btree, BinaryTreeNode *node, const void *data);
BinaryTreeNode *binary_tree_search(BinaryTree *btree, const void *data);

void binary_tree_remove(BinaryTree *btree, const void *data);

void binary_tree_traverse_preorder(BinaryTree *btree, void (*traverse)(void *data));
void binary_tree_traverse_inorder(BinaryTree *btree, void (*traverse)(void *data));
void binary_tree_traverse_postorder(BinaryTree *btree, void (*traverse)(void *data));
void binary_tree_traverse_levelorder(BinaryTree *btree, void (*traverse)(void *data));

#endif
