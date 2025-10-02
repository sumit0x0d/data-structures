#include <stdlib.h>
#include <string.h>

#include "red-black-tree-node.h"

RedBlackTreeNode RedBlackTreeNode_Create(const DS_Generic data, DS_Size data_size)
{
    RedBlackTreeNode node = (RedBlackTreeNode)malloc(sizeof (RedBlackTreeNode));
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

DS_Void RedBlackTreeNode_Destroy(RedBlackTreeNode node)
{
    free(node->data);
    free(node);
}
