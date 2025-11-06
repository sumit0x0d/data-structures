#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <stddef.h>

typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeNode BinaryTreeNode;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} BinaryTreeUnaryCallback;

__attribute__((visibility("default")))
BinaryTree *BinaryTree_Create(size_t data_size);

__attribute__((visibility("default")))
void BinaryTree_Destroy(BinaryTree *this);

__attribute__((visibility("default")))
void BinaryTree_InsertLeft(BinaryTree *this, BinaryTreeNode *node, const void *data);

__attribute__((visibility("default")))
void BinaryTree_InsertRight(BinaryTree *this, BinaryTreeNode *node, const void *data);

__attribute__((visibility("default")))
void BinaryTree_Remove(BinaryTree *this, BinaryTreeNode *node);

__attribute__((visibility("default")))
void BinaryTree_TraversePreorder(BinaryTree *this, BinaryTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinaryTree_TraverseInorder(BinaryTree *this, BinaryTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinaryTree_TraversePostorder(BinaryTree *this, BinaryTreeUnaryCallback unary_callback);

__attribute__((visibility("default")))
void BinaryTree_TraverseLevelorder(BinaryTree *this, BinaryTreeUnaryCallback unary_callback);

#endif
