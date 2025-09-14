#include <stdlib.h>

#include <binary-tree-node.h>

BinaryTreeNode BinaryTreeNode_Create(const DS_Data data, DS_Size sData)
{
    BinaryTreeNode node = (BinaryTreeNode)malloc(sizeof (BinaryTreeNode));
    if (!node) {
        return NULL;
    } 
    node->data = malloc(sData);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, sData);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void BinaryTreeNode_Destroy(BinaryTreeNode node)
{
    free(node->data);
    free(node);
}