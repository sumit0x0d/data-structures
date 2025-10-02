#include "singly-linked-list-node.h"

typedef SinglyLinkedListNode Node;

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Generic data,
    DS_Size data_size)
{
    Node node = (Node)malloc(sizeof (struct SinglyLinkedListNode));
    if (!node) {
        return NULL;
    }
    node->data = malloc(data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, data_size);
    return node;
}

DS_Void SinglyLinkedListNode_Destroy(Node node)
{
    free(node->data);
    free(node);
}
