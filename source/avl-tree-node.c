#include <stdlib.h>
#include <string.h>

#include "avl-tree-node.h"

typedef AvlTreeNode Node;

Node AvlTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
    Node node = (Node)malloc(sizeof (struct AvlTreeNode));
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

DS_Size AvlTreeNode_GetHeight(Node node, CircularBuffer circular_buffer)
{
    DS_Size height = 0;
    CircularBuffer_PushBack(circular_buffer, node);
    while (!CircularBuffer_IsEmpty(circular_buffer)) {
        node = CircularBuffer_GetFrontData(circular_buffer);
        CircularBuffer_PopFront(circular_buffer);
        if (node->left) {
          CircularBuffer_PushBack(circular_buffer, node->left);
        }
        if (node->right) {
          CircularBuffer_PushBack(circular_buffer, node->right);
        }
        height++;
    }
    return height;
}

DS_Void AvlTreeNode_UpdateBalanceFactor(Node node, CircularBuffer circular_buffer)
{
    DS_Size left_height = 0;
    DS_Size right_height = 0;
    if (node->left) {
        left_height = AvlTreeNode_GetHeight(node->left, circular_buffer);
    }
    if (node->right) {
        right_height = AvlTreeNode_GetHeight(node->right, circular_buffer);
    }
    node->balance_factor = (int)(left_height - right_height);
}

Node AvlTreeNode_GetPredecessor(Node node)
{
    Node left = node->left;
    Node previous = node;
    free(node->data);
    node = left;
    while (node->right) {
        node = node->right;
    }
    previous->data = node->data;
    left = node->left;
    previous = node->parent;
    previous->right = left;
    if (left) {
        left->parent = previous;
    }
    free(node);
    return previous;
}

Node AvlTreeNode_GetSuccessor(Node node)
{
    Node right = node->right;
    Node previous = node;
    free(node->data);
    node = right;
    while (node->left) {
        node = node->left;
    }
    previous->data = node->data;
    right = node->right;
    previous = node->parent;
    previous->left = right;
    if (right) {
        right->parent = previous;
    }
    free(node);
    return previous;
}