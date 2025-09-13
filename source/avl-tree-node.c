#include <stdlib.h>
#include <string.h>

#include <avl-tree-node.h>

typedef AvlTreeNode Node;

Node AvlTreeNode_Create(const DS_Data data, DS_Size sData)
{
    Node node = (Node)malloc(sizeof (struct avl_tree_node));
    if (!node) {
        return NULL;
    }
    node->data = malloc(sData);
    if (!node->data){
        free(node);
        return NULL;
    }
    memcpy(node->data, data, sData);
    node->left = NULL;
    node->right = NULL;
    node->balance_factor = 0;
    return node;
}

void AvlTreeNode_Destroy(Node node)
{
    free(node->data);
    free(node);
}

DS_Size AvlTreeNode_GetHeight(Node node, CircularBuffer *cBuffer)
{
    DS_Size height = 0;
    CircularBuffer_PushBack(cBuffer, node);
    while (!CircularBuffer_IsEmpty(cBuffer)) {
        node = CircularBuffer_GetFrontData(cBuffer);
        CircularBuffer_PopFront(cBuffer);
        if (node->left) {
            CircularBuffer_PushBack(cBuffer, node->left);
        }
        if (node->right) {
            CircularBuffer_PushBack(cBuffer, node->right);
        }
        height++;
    }
    return height;
}

void AvlTreeNode_UpdateBalanceFactor(Node node, CircularBuffer *cBuffer)
{
    DS_Size hnLeft = 0;
    DS_Size hnRight = 0;
    if (node->left) {
        hnLeft = AvlTreeNode_GetHeight(node->left, cBuffer);
    }
    if (node->right) {
        hnRight = AvlTreeNode_GetHeight(node->right, cBuffer);
    }
    node->balance_factor = (int)(hnLeft - hnRight);
}

Node AvlTreeNode_GetPredecessor(Node node)
{
    Node nLeft = node->left;
    Node nPrevious = node;
    free(node->data);
    node = nLeft;
    while (node->right) {
        node = node->right;
    }
    nPrevious->data = node->data;
    nLeft = node->left;
    nPrevious = node->parent;
    nPrevious->right = nLeft;
    if (nLeft) {
        nLeft->parent = nPrevious;
    }
    free(node);
    return nPrevious;
}

Node AvlTreeNode_GetSuccessor(Node node)
{
    Node nRight = node->right;
    Node nPrevious = node;
    free(node->data);
    node = nRight;
    while (node->left) {
        node = node->left;
    }
    nPrevious->data = node->data;
    nRight = node->right;
    nPrevious = node->parent;
    nPrevious->left = nRight;
    if (nRight) {
        nRight->parent = nPrevious;
    }
    free(node);
    return nPrevious;
}