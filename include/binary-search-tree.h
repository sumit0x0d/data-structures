#ifndef DATA_STRUCTURES_BINARY_SEARCH_TREE_H
#define DATA_STRUCTURES_BINARY_SEARCH_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct binary_search_tree BinarySearchTree;
typedef struct binary_search_tree_node BinarySearchTreeNode;

BinarySearchTree *binary_search_tree_create(size_t dsize, int (*compare)(const void *data1, const void *data2));
void binary_search_tree_destroy(BinarySearchTree *bstree);

void binary_search_tree_insert(BinarySearchTree *bstree, const void *data);

BinarySearchTreeNode *binary_search_tree_search(BinarySearchTree *bstree, const void *data);

void binary_search_tree_remove(BinarySearchTree *bstree, const void *data);

void binary_search_tree_traverse_preorder(BinarySearchTree *bstree, void (*traverse)(void *data));
void binary_search_tree_traverse_inorder(BinarySearchTree *bstree, void (*traverse)(void *data));
void binary_search_tree_traverse_postorder(BinarySearchTree *bstree, void (*traverse)(void *data));
void binary_search_tree_traverse_levelorder(BinarySearchTree *bstree, void (*traverse)(void *data));

#endif
