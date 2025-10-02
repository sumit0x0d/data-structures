#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>
#include <circular-buffer.h>

#include "red-black-tree-node.h"

typedef RedBlackTreeNode Node;

struct red_black_tree {
    Node root;
    DS_Size data_size;
    DS_Size size;
    DS_CallbackCompare compare_callback;
    DS_Generic compare_context;
};

static DS_Void _RotateRight(RedBlackTree tree, Node node);
static DS_Void _RotateLeftRight(RedBlackTree tree, Node node);
static DS_Void _RotateLeft(RedBlackTree tree, Node node);
static DS_Void _RotateRightLeft(RedBlackTree tree, Node node);
static DS_Void _Rebalance(RedBlackTree tree, Node node);

RedBlackTree RedBlackTree_Create(DS_Size size, DS_CallbackCompare compare_callback, DS_Generic compare_context)
{
    RedBlackTree tree = (RedBlackTree)malloc(sizeof (RedBlackTree));
    if (!tree) {
        return NULL;
    }
    tree->root = NULL;
    tree->data_size = size;
    tree->size = 0;
    tree->compare_callback = compare_callback;
    tree->compare_context = compare_context;
    return tree;
}

DS_Void RedBlackTree_Destroy(RedBlackTree tree)
{
    Node node = tree->root;
    CircularBuffer *buffer = CircularBuffer_Create(sizeof (Node ), tree->size);
    free(node->data);
    CircularBuffer_PushBack(buffer, node);
    while (!CircularBuffer_IsEmpty(buffer)) {
        node = (Node )CircularBuffer_GetFrontData(buffer);
        CircularBuffer_PopFront(buffer);
        if (node->left) {
            RedBlackTreeNode_Destroy(node);
            // CircularBuffer_PushBack(buffer, node->left);
        }
        if (node->right) {
            RedBlackTreeNode_Destroy(node);
            // CircularBuffer_PushBack(buffer, node->right);
        }
    }
    CircularBuffer_Destroy(buffer);
    free(tree);
}

DS_Size RedBlackTree_GetSize(RedBlackTree tree)
{
    return tree->size;
}

Node RedBlackTree_Search(RedBlackTree tree, const DS_Generic data)
{
    Node node = tree->root;
    while (node) {
        int compare = tree->compare_callback(data, node->data, tree->compare_context);
        if (compare == 0) {
            return node;
        } else if (compare < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return NULL;
}

DS_Void RedBlackTree_Insert(RedBlackTree tree, const DS_Generic data)
{
    if (!tree->root) {
        tree->root = RedBlackTreeNode_Create(data, tree->data_size);
        tree->root->parent = NULL;
        tree->root->color = 1;
        tree->size++;
        return;
    }
    Node node = tree->root;
    Node pNode = tree->root->parent;
    int compare = 0;
    while (node) {
        compare = tree->compare_callback(data, node->data, tree->compare_context);
        if (compare == 0) {
            return;
        }
        pNode = node;
        if (compare < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    node = _RedBlackTreeNode_Create(data, tree->data_size);
    node->parent = pNode;
    node->color = 0;
    compare = tree->compare_callback(data, pNode->data, tree->compare_context);
    if (compare < 0) {
        pNode->left = node;
    } else {
        pNode->right = node;
    }
    _Rebalance(tree, pNode);
    tree->size++;
}

// DS_Void red_black_tree_remove(RedBlackTree tree, int data)
// {
// }

static DS_Void _RotateRight(RedBlackTree tree, Node node)
{
    Node nLeft = node->left;
    node->left = nLeft->right;
    if (node->left) {
        node->left->parent = node;
    }
    nLeft->parent = node->parent;
    if (nLeft->parent) {
        if (nLeft->parent->left == node) {
            nLeft->parent->left = nLeft;
        } else {
            nLeft->parent->right = nLeft;
        }
    } else {
        tree->root = nLeft;
    }
    node->parent = nLeft;
    nLeft->right = node;
}

static DS_Void _RotateLeftRight(RedBlackTree tree, Node node)
{
    Node nLeft = node->left;
    Node nlRight = node->left->right;
    nLeft->right = nlRight->left;
    if (nLeft->right) {
        nLeft->right->parent = nLeft;
    }
    node->left = nlRight->right;
    if (node->left) {
        node->left->parent = node;
    }
    nlRight->left = nLeft;
    nLeft->parent = nlRight;
    nlRight->parent = node->parent;
    if (nlRight->parent) {
        if (nlRight->parent->left == node) {
            nlRight->parent->left = nlRight;
        } else {
            nlRight->parent->right = nlRight;
        }
    } else {
        tree->root = nlRight;
    }
    node->parent = nlRight;
    nlRight->right = node;
}

static DS_Void _RotateLeft(RedBlackTree tree, Node node)
{
    Node nRight = node->right; 
    node->right = nRight->left;
    if (node->right) {
        node->right->parent = node;
    }
    nRight->parent = node->parent;
    if (nRight->parent) {
        if (nRight->parent->left == node) {
            nRight->parent->left = nRight;
        } else {
            nRight->parent->right = nRight;
        }
    } else {
        tree->root = nRight;
    }
    node->parent = nRight;
    nRight->left = node;
}

static DS_Void _RotateRightLeft(RedBlackTree tree, Node node)
{
    Node nRight = node->right;
    Node nrLeft = node->right->left;
    nRight->left = nrLeft->right;
    if (nRight->left) {
        nRight->left->parent = nRight;
    }
    node->right = nrLeft->left;
    if (node->right) {
        node->right->parent = node;
    }
    nrLeft->right = nRight;
    nRight->parent = nrLeft;
    nrLeft->parent = node->parent;
    if (nrLeft->parent) {
        if (nrLeft->parent->left == node) {
            nrLeft->parent->left = nrLeft;
        } else {
            nrLeft->parent->right = nrLeft;
        }
    } else {
        tree->root = nrLeft;
    }
    node->parent = nrLeft;
    nrLeft->left = node;
}

static DS_Void _Rebalance(RedBlackTree tree, Node node)
{
    while (node) {
        if (node->color == RED_BLACK_TREE_NODE_COLOR_RED) {
            if (node->parent->left == node) {
                if (!node->parent->right || node->parent->right->color == 1) {
                    _RotateRight(tree, node);
                }
                else if (node->parent->right || node->parent->right->color == 0) {
                }
            }
        }
        if (node->parent->left == node) {
            if (node->color == 0 &&
                (!node->parent->right || node->parent->right->color == 1)) {
            }
            if (node->color == 0 &&
                (node->parent->right && node->parent->right->color == 0)) {
                node->parent->color = 1;
            }
        } else {
            if (node->color == 0 &&
                (!node->parent->left || node->parent->left->color == 1)) {
                _RotateLeft(tree, node);
                _RotateRightLeft(tree, node);
                _RotateLeftRight(tree, node);
                _RotateRight(tree, node);
            }
            if (node->color == 0 &&
                (node->parent->left && node->parent->left->color == 0)) {
                node->parent->color = 1;
            }
        }
        tree->root = node->parent;
    }
}
