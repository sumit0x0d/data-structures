#include <stdlib.h>

#include <red-black-tree-node.h>

static RedBlackTreeNode RedBlackTreeNode_Create(const DS_Data data, DS_Size sData)
{
    RedBlackTreeNode node = (RedBlackTreeNode)malloc(sizeof (RedBlackTreeNode));
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

static DS_Void RedBlackTreeNode_Destroy(RedBlackTreeNode node)
{
    free(node->data);
    free(node);
}
