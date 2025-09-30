#include <stdlib.h>
#include <string.h>

#include <avl-tree-node.h>

typedef AvlTreeNode Node;

Node AvlTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
    Node node = (Node)malloc(sizeof (struct avl_tree_node));
    if (!node) {
        return NULL;
    }
    node->data = malloc(data_size);
    if (!node->data){
        free(node);
        return NULL;
    }
    memcpy(node->data, data, data_size);
    node->left = NULL;
    node->right = NULL;
    node->balance_factor = 0;
    return node;
}

DS_Void AvlTreeNode_Destroy(Node node)
{
    free(node->data);
    free(node);
}

DS_Size AvlTreeNode_GetHeight(Node node, CircularBuffer buffer)
{
    DS_Size height = 0;
    CircularBuffer_PushBack(buffer, node);
    while (!CircularBuffer_IsEmpty(buffer)) {
        node = CircularBuffer_GetFrontData(buffer);
        CircularBuffer_PopFront(buffer);
        if (node->left) {
            CircularBuffer_PushBack(buffer, node->left);
        }
        if (node->right) {
            CircularBuffer_PushBack(buffer, node->right);
        }
        height++;
    }
    return height;
}

DS_Void AvlTreeNode_UpdateBalanceFactor(Node node, CircularBuffer buffer)
{
    DS_Size hnLeft = 0;
    DS_Size hnRight = 0;
    if (node->left) {
        hnLeft = AvlTreeNode_GetHeight(node->left, buffer);
    }
    if (node->right) {
        hnRight = AvlTreeNode_GetHeight(node->right, buffer);
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