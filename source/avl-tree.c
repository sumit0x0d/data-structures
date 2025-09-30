#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>
#include <circular-buffer.h>
#include <stack.h>

#include "avl-tree-node.h"

#include "generic-binary-tree-traverse.h"

typedef AvlTreeNode Node;

struct avl_tree {
    Node root;
    DS_Size data_size;
    DS_Size size;
    DS_CallbackCompare compare_callback;
    DS_Generic compare_context;
};

static DS_Void _Rebalance(AvlTree tree, Node node, CircularBuffer buffer);
static DS_Void _RotateRight(AvlTree tree, Node node);
static DS_Void _RotateLeftRight(AvlTree tree, Node node);
static DS_Void _RotateLeft(AvlTree tree, Node node);
static DS_Void _RotateRightLeft(AvlTree tree, Node node);

AvlTree AvlTree_Create(DS_Size data_size, DS_CallbackCompare compare_callback, DS_Generic compare_context)
{
    AvlTree tree = (AvlTree)malloc(sizeof (struct avl_tree));
    if (!tree) {
        return NULL;
    }
    tree->root = NULL;
    tree->data_size = data_size;
    tree->size = 0;
    tree->compare_callback = compare_callback;
    tree->compare_context = compare_context;
    return tree;
}

DS_Void AvlTree_Destroy(AvlTree tree)
{
    CircularBuffer buffer = CircularBuffer_Create(sizeof (Node), tree->size);
    Node node = tree->root;
    free(node->data);
    CircularBuffer_PushBack(buffer, node);
    while (!CircularBuffer_IsEmpty(buffer)) {
        node = (Node)CircularBuffer_GetFrontData(buffer);
        CircularBuffer_PopFront(buffer);
        if (node->left) {
            free(node->data);
            CircularBuffer_PushBack(buffer, node->left);
        }
        if (node->right) {
            free(node->data);
            CircularBuffer_PushBack(buffer, node->right);
        }
    }
    CircularBuffer_Destroy(buffer);
    free(tree);
}

Node AvlTree_Search(AvlTree tree, const DS_Generic data)
{
    Node node = tree->root;
    while (node) {
        switch (tree->compare_callback(node->data, data, tree->compare_context)) {
        case -1:
            node = node->left;
            break;
        case 0:
            return node;
        case 1:
            node = node->right;
            break;
        }
    }
    return NULL;
}

DS_Void AvlTree_Insert(AvlTree tree, const DS_Generic data)
{
    if (!tree->root) {
        tree->root = AvlTreeNode_Create(data, tree->data_size);
        tree->root->parent = NULL;
        tree->size++;
        return;
    }
    CircularBuffer buffer = CircularBuffer_Create(sizeof (struct avl_tree_node), (tree->size + 2) / 2);
    Node node = tree->root;
    Node parent = tree->root->parent;
    int compare = 0;
    while (node) {
        compare = tree->compare_callback(node->data, data, tree->compare_context);
        if (compare == 0) {
            CircularBuffer_Destroy(buffer);
            return;
        }
        parent = node;
        if (compare < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    node = AvlTreeNode_Create(data, tree->data_size);
    node->parent = parent;
    if (compare < 0) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    _Rebalance(tree, parent, buffer);
    CircularBuffer_Destroy(buffer);
    tree->size++;
}

DS_Void AvlTree_Remove(AvlTree tree, const DS_Generic data)
{
    CircularBuffer buffer = CircularBuffer_Create(sizeof (struct avl_tree_node), (tree->size + 2) / 2);
    Node node = tree->root;
    Node parent = tree->root->parent;
    while (node) {
        int compare = tree->compare_callback(data, node->data, tree->compare_context);
        if (compare == 0) {
            break;
        }
        parent = node;
        if (compare < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (!node) {
        return;
    }
    if (!node->left && !node->right) {
        if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, parent, buffer);
    } else if (!node->left) {
        if (parent->right == node) {
            parent->right = node->right;
        } else {
            parent->left = node->right;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, parent, buffer);
    } else if (!node->right) {
        if (parent->left == node) {
            parent->left = node->left;
        } else {
            parent->right = node->left;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, parent, buffer);
    } else {
        if (tree->root->balance_factor < 0) {
            node = AvlTreeNode_GetPredecessor(node);
        } else {
            node = AvlTreeNode_GetSuccessor(node);
        }
        _Rebalance(tree, node, buffer);
    }
    CircularBuffer_Destroy(buffer);
    tree->size--;
}

DS_Void AvlTree_TraversePreorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context)
{
}

DS_Void AvlTree_TraverseInorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context)
{
}

DS_Void AvlTree_TraversePostorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context)
{
}

DS_Void AvlTree_TraverseLevelorder(AvlTree tree, DS_CallbackUnary unary_callback, DS_Generic unary_context)
{
}


static DS_Void _RotateRight(AvlTree tree, Node node)
{
    Node left = node->left;
    node->left = left->right;
    if (node->left) {
        node->left->parent = node;
    }
    left->parent = node->parent;
    if (left->parent) {
        if (left->parent->left == node) {
            left->parent->left = left;
        } else {
            left->parent->right = left;
        }
    } else {
        tree->root = left;
    }
    node->parent = left;
    left->right = node;
}

static DS_Void _RotateLeftRight(AvlTree tree, Node node)
{
    Node left = node->left;
    Node left_right = node->left->right;
    left->right = left_right->left;
    if (left->right) {
        left->right->parent = left;
    }
    node->left = left_right->right;
    if (node->left) {
        node->left->parent = node;
    }
    left_right->left = left;
    left->parent = left_right;
    left_right->parent = node->parent;
    if (left_right->parent) {
        if (left_right->parent->left == node) {
            left_right->parent->left = left_right;
        } else {
            left_right->parent->right = left_right;
        }
    } else {
        tree->root = left_right;
    }
    node->parent = left_right;
    left_right->right = node;
}

static DS_Void _RotateLeft(AvlTree tree, Node node)
{
    Node right = node->right;
    node->right = right->left;
    if (node->right) {
        node->right->parent = node;
    }
    right->parent = node->parent;
    if (right->parent) {
        if (right->parent->left == node) {
            right->parent->left = right;
        } else {
            right->parent->right = right;
        }
    } else {
        tree->root = right;
    }
    node->parent = right;
    right->left = node;
}

static DS_Void _RotateRightLeft(AvlTree tree, Node node)
{
    Node right = node->right;
    Node right_left = node->right->left;
    right->left = right_left->right;
    if (right->left) {
        right->left->parent = right;
    }
    node->right = right_left->left;
    if (node->right) {
        node->right->parent = node;
    }
    right_left->right = right;
    right->parent = right_left;
    right_left->parent = node->parent;
    if (right_left->parent) {
        if (right_left->parent->left == node) {
            right_left->parent->left = right_left;
        } else {
            right_left->parent->right = right_left;
        }
    } else {
        tree->root = right_left;
    }
    node->parent = right_left;
    right_left->left = node;
}

static DS_Void _Rebalance(AvlTree tree, Node node, CircularBuffer buffer)
{
    while (node) {
        AvlTreeNode_UpdateBalanceFactor(node, buffer);
        if (node->balance_factor == -2) {
            if (node->left->balance_factor == -1) {
                _RotateRight(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, buffer);
                AvlTreeNode_UpdateBalanceFactor(node->right, buffer);
            } else if (node->left->balance_factor == 1) {
                _RotateLeftRight(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, buffer);
            }
        } else if (node->balance_factor == 2) {
            if (node->right->balance_factor == 1) {
                _RotateLeft(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, buffer);
                AvlTreeNode_UpdateBalanceFactor(node->left, buffer);
            } else if (node->right->balance_factor == -1) {
                _RotateRightLeft(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, buffer);
            }
        }
        node = node->parent;
    }
}
