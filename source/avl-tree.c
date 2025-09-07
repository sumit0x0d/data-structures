#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>
#include <circular-buffer.h>
#include <stack.h>

#include "avl-tree-node.h"

typedef AvlTreeNode Node;

struct avl_tree {
    Node *root;
    DS_Size data_size;
    DS_Size size;
    DS_FunctionCompare compare;
    DS_Data user_data;
};

static void _Rebalance(AvlTree *aTree, Node *node, CircularBuffer *cBuffer);
static void _RotateRight(AvlTree *aTree, Node *node);
static void _RotateLeftRight(AvlTree *aTree, Node *node);
static void _RotateLeft(AvlTree *aTree, Node *node);
static void _RotateRightLeft(AvlTree *aTree, Node *node);

AvlTree *AvlTree_Create(DS_Size sData, DS_FunctionCompare fCompare, DS_Data dUser)
{
    AvlTree *aTree = (AvlTree *)malloc(sizeof (AvlTree));
    if (!aTree) {
        return NULL;
    }
    aTree->root = NULL;
    aTree->data_size = sData;
    aTree->size = 0;
    aTree->compare = fCompare;
    aTree->user_data = dUser;
    return aTree;
}

void AvlTree_Destroy(AvlTree *aTree)
{
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), aTree->size);
    Node *node = aTree->root;
    free(node->data);
    CircularBuffer_PushBack(cBuffer, node);
    while (!CircularBuffer_IsEmpty(cBuffer)) {
        node = (Node *)CircularBuffer_GetFrontData(cBuffer);
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
    free(aTree);
}

Node *AvlTree_Search(AvlTree *aTree, const DS_Data data)
{
    Node *node = aTree->root;
    while (node) {
        switch (aTree->compare(node->data, data, aTree->user_data)) {
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

void AvlTree_Insert(AvlTree *aTree, const DS_Data data)
{
    if (!aTree->root) {
        aTree->root = AvlTreeNode_Create(data, aTree->data_size);
        aTree->root->parent = NULL;
        aTree->size++;
        return;
    }
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), (aTree->size + 2) / 2);
    Node *node = aTree->root;
    Node *pnode = aTree->root->parent;
    int compare = 0;
    while (node) {
        compare = aTree->compare(node->data, data, aTree->user_data);
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
    node = AvlTreeNode_Create(data, aTree->data_size);
    node->parent = pnode;
    if (compare < 0) {
        pnode->left = node;
    } else {
        pnode->right = node;
    }
    _Rebalance(aTree, pnode, cBuffer);
    CircularBuffer_Destroy(cBuffer);
    aTree->size++;
}

void AvlTree_Remove(AvlTree *aTree, const DS_Data data)
{
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), (aTree->size + 2) / 2);
    Node *node = aTree->root;
    Node *pnode = aTree->root->parent;
    while (node) {
        int compare = aTree->compare(data, node->data, aTree->user_data);
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
        _Rebalance(aTree, pnode, cBuffer);
    }
    else if (!node->left) {
        if (pnode->right == node) {
            pnode->right = node->right;
        } else {
            pnode->left = node->right;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(aTree, pnode, cBuffer);
    }
    else if (!node->right) {
        if (pnode->left == node) {
            pnode->left = node->left;
        }
        else {
            pnode->right = node->left;
        }
        AvlTreeNode_Destroy(node);
        _Rebalance(aTree, pnode, cBuffer);
    } else {
        if (aTree->root->balance_factor < 0) {
            node = AvlTreeNode_GetPredecessor(node);
        } else {
            node = AvlTreeNode_GetSuccessor(node);
        }
        _Rebalance(aTree, node, cBuffer);
    }
    CircularBuffer_Destroy(cBuffer);
    aTree->size--;
}

void AvlTree_TraversePreorder(AvlTree *aTree, DS_FunctionTraverse atTraverse, DS_Data dUser)
{
    Node *node = aTree->root;
    Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
    while (node || !Stack_IsEmpty(stack)) {
        if (node) {
            Stack_Push(stack, node);
            atTraverse(node->data, dUser);
            node = node->left;
        } else {
            node = (Node *)Stack_GetTop(stack);
            Stack_Pop(stack);
            node = node->right;
        }
    }
    Stack_Destroy(stack);
}

void AvlTree_TraverseInorder(AvlTree *aTree, DS_FunctionTraverse atTraverse, DS_Data dUser)
{
    Node *node = aTree->root;
    Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
    while (node || !Stack_IsEmpty(stack)) {
        if (node) {
            Stack_Push(stack, node);
            node = node->left;
        } else {
            node = (Node *)Stack_GetTop(stack);
            Stack_Pop(stack);
            atTraverse(node->data, dUser);
            node = node->right;
        }
    }
    Stack_Destroy(stack);
}

void AvlTree_TraversePostorder(AvlTree *aTree, DS_FunctionTraverse atTraverse, DS_Data dUser)
{
    Node *node = aTree->root;
    Stack *stack = Stack_Create(sizeof (Node *), aTree->size);
    while (node || !Stack_IsEmpty(stack)) {
        if (node) {
            Stack_Push(stack, node);
            atTraverse(node->data, dUser);
            node = node->left;
        } else {
            node = (Node *)Stack_GetTop(stack);
            Stack_Pop(stack);
            node = node->right;
        }
    }
    Stack_Destroy(stack);
}

void AvlTree_TraverseLevelorder(AvlTree *aTree, DS_FunctionTraverse atTraverse, DS_Data dUser)
{
    Node *node = aTree->root;
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (Node *), aTree->size);
    atTraverse(node->data, dUser);
    CircularBuffer_PushBack(cBuffer, node);
    while (!CircularBuffer_IsEmpty(cBuffer)) {
        node = CircularBuffer_GetFrontData(cBuffer);
        CircularBuffer_PopFront(cBuffer);
        if (node->left) {
            atTraverse(node->data, dUser);
            CircularBuffer_PushBack(cBuffer, node->left);
        }
        if (node->right) {
            atTraverse(node->data, dUser);
            CircularBuffer_PushBack(cBuffer, node->right);
        }
    }
    CircularBuffer_Destroy(cBuffer);
}


static void _RotateRight(AvlTree *tree, Node *node)
{
    Node *nLeft = node->left;
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

static void _RotateLeftRight(AvlTree *aTree, Node *node)
{
    Node *nLeft = node->left;
    Node *nlRight = node->left->right;
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
        aTree->root = nlRight;
    }
    node->parent = nlRight;
    nlRight->right = node;
}

static void _RotateLeft(AvlTree *aTree, Node *node)
{
    Node *nRight = node->right;
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
        aTree->root = nRight;
    }
    node->parent = nRight;
    nRight->left = node;
}

static void _RotateRightLeft(AvlTree *aTree, Node *node)
{
    Node *nRight = node->right;
    Node *nrLeft = node->right->left;
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
        aTree->root = nrLeft;
    }
    node->parent = nrLeft;
    nrLeft->left = node;
}

static void _Rebalance(AvlTree *aTree, Node *node, CircularBuffer *cBuffer)
{
    while (node) {
        AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
        if (node->balance_factor == -2) {
            if (node->left->balance_factor == -1) {
                _RotateRight(aTree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                AvlTreeNode_UpdateBalanceFactor(node->right, cBuffer);
            } else if (node->left->balance_factor == 1) {
                _RotateLeftRight(aTree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
            }
        } else if (node->balance_factor == 2) {
            if (node->right->balance_factor == 1) {
                _RotateLeft(aTree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
                AvlTreeNode_UpdateBalanceFactor(node->left, cBuffer);
            }
            else if (node->right->balance_factor == -1) {
                _RotateRightLeft(aTree, node);
                AvlTreeNode_UpdateBalanceFactor(node, cBuffer);
            }
        }
        node = node->parent;
    }
}
