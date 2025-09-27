#include <stdlib.h>

#include <binary-tree-node.h>

BinaryTreeNode BinaryTreeNode_Create(const DS_Data data, DS_Size data_size)
{
    BinaryTreeNode node = (BinaryTreeNode)malloc(sizeof (BinaryTreeNode));
    if (!node) {
        return NULL;
    } 
    node->data = malloc(data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, data_size);
    node->left = NULL;
    node->right = NULL;
    return node;
}

DS_Void BinaryTreeNode_Destroy(BinaryTreeNode node)
{
    free(node->data);
    free(node);
}