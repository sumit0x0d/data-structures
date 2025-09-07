#include <stdlib.h>

#include <red-black-tree-node.h>

typedef RedBlackTreeNode Node;

static Node *RedBlackTreeNode_Create(const DS_Data data, DS_Size sData)
{
    Node *node = (Node *)malloc(sizeof (Node));
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

static void RedBlackTreeNode_Destroy(Node *node)
{
    free(node->data);
    free(node);
}
