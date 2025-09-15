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
    DS_FunctionCompare compare;
    DS_Context context;
};

static DS_Void _Rebalance(AvlTree tree, Node node, CircularBuffer *cBuffer);
static DS_Void _RotateRight(AvlTree tree, Node node);
static DS_Void _RotateLeftRight(AvlTree tree, Node node);
static DS_Void _RotateLeft(AvlTree tree, Node node);
static DS_Void _RotateRightLeft(AvlTree tree, Node node);

AvlTree AvlTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Context context)
{
    AvlTree tree = (AvlTree)malloc(sizeof (struct avl_tree));
    if (!tree) {
        return NULL;
    }
    tree->root = NULL;
    tree->data_size = sData;
    tree->size = 0;
    tree->compare = fCompare;
    tree->context = context;
    return tree;
}

DS_Void AvlTree_Destroy(AvlTree tree)
{
    CircularBuffer cBuffer = CircularBuffer_Create(sizeof (Node), tree->size);
    Node node = tree->root;
    free(node->data);
    CircularBuffer_PushBack(cBuffer, node);
    while (!CircularBuffer_IsEmpty(cBuffer)) {
        node = (Node)CircularBuffer_GetFrontData(cBuffer);
        CircularBuffer_PopFront(cBuffer);
        if (node->left) {
            free(node->data);
            CircularBuffer_PushBack(cBuffer, node->left);
        }
        if (node->right) {
            free(node->data);
            CircularBuffer_PushBack(cBuffer, node->right);
        }
    }
    CircularBuffer_Destroy(cBuffer);
    free(tree);
}

Node AvlTree_Search(AvlTree tree, const DS_Data data)
{
    Node node = tree->root;
    while (node) {
        switch (tree->compare(node->data, data, tree->context)) {
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

DS_Void AvlTree_Insert(AvlTree tree, const DS_Data data)
{
    if (!tree->root) {
        tree->root = AvlTreeNode_Create(data, tree->data_size);
        tree->root->parent = NULL;
        tree->size++;
        return;
    }
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (struct avl_tree_node), (tree->size + 2) / 2);
    Node node = tree->root;
    Node pnode = tree->root->parent;
    int compare = 0;
    while (node) {
        compare = tree->compare(node->data, data, tree->context);
        if (compare == 0) {
            CircularBuffer_Destroy(cBuffer);
            return;
        }
        pnode = node;
        if (compare < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    node = AvlTreeNode_Create(data, tree->data_size);
    node->parent = pnode;
    if (compare < 0) {
        pnode->left = node;
    } else {
        pnode->right = node;
    }
    _Rebalance(tree, pnode, cBuffer);
    CircularBuffer_Destroy(cBuffer);
    tree->size++;
}

DS_Void AvlTree_Remove(AvlTree tree, const DS_Data data)
{
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (struct avl_tree_node), (tree->size + 2) / 2);
    Node node = tree->root;
    Node pnode = tree->root->parent;
    while (node) {
        int compare = tree->compare(data, node->data, tree->context);
        if (compare == 0) {
            break;
        }
        pnode = node;
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
        if (pnode->left == node) {
            pnode->left = NULL;
        } else {
            pnode->right = NULL;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, pnode, cBuffer);
    }
    else if (!node->left) {
        if (pnode->right == node) {
            pnode->right = node->right;
        } else {
            pnode->left = node->right;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, pnode, cBuffer);
    }
    else if (!node->right) {
        if (pnode->left == node) {
            pnode->left = node->left;
        }
        else {
            pnode->right = node->left;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(tree, pnode, cBuffer);
    } else {
        if (tree->root->balance_factor < 0) {
            node = AvlTreeNode_GetPredecessor(node);
        } else {
            node = AvlTreeNode_GetSuccessor(node);
        }
        _Rebalance(tree, node, cBuffer);
    }
    CircularBuffer_Destroy(cBuffer);
    tree->size--;
}

DS_Void AvlTree_TraversePreorder(AvlTree tree, DS_FunctionUnary fUnary, DS_Context cUnary)
{
}

DS_Void AvlTree_TraverseInorder(AvlTree tree, DS_FunctionUnary fUnary, DS_Context cUnary)
{
}

DS_Void AvlTree_TraversePostorder(AvlTree tree, DS_FunctionUnary fUnary, DS_Context cUnary)
{
}

DS_Void AvlTree_TraverseLevelorder(AvlTree tree, DS_FunctionUnary fUnary, DS_Context cUnary)
{
}


static DS_Void _RotateRight(AvlTree tree, Node node)
{
    Node nLeft = node->left;
    node->left = nLeft->right;
    if (node->left) {
        node->left->parent = node;
    }
    nLeft->parent = node->parent;
    if (nLeft->parent) {
        if (nLeft->parent->left == node) nLeft->parent->left = nLeft;
        else nLeft->parent->right = nLeft;
    } else {
        tree->root = nLeft;
    }
    node->parent = nLeft;
    nLeft->right = node;
}

static DS_Void _RotateLeftRight(AvlTree tree, Node node)
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

static DS_Void _RotateLeft(AvlTree tree, Node node)
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

static DS_Void _RotateRightLeft(AvlTree tree, Node node)
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

static DS_Void _Rebalance(AvlTree tree, Node node, CircularBuffer *cBuffer)
{
    while (node) {
        AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
        if (node->balance_factor == -2) {
            if (node->left->balance_factor == -1) {
                _RotateRight(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                AvlTreeNode_UpdateBalanceFactor(node->right, cBuffer);
            } else if (node->left->balance_factor == 1) {
                _RotateLeftRight(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
            }
        } else if (node->balance_factor == 2) {
            if (node->right->balance_factor == 1) {
                _RotateLeft(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                AvlTreeNode_UpdateBalanceFactor(node->left, cBuffer);
            }
            else if (node->right->balance_factor == -1) {
                _RotateRightLeft(tree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
            }
        }
        node = node->parent;
    }
}
