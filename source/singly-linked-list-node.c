#include "singly-linked-list-node.h"

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Data data, DS_Size data_size)
{
    SinglyLinkedListNode node = (SinglyLinkedListNode)malloc(sizeof (struct singly_linked_list_node));
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

DS_Void SinglyLinkedListNode_Destroy(SinglyLinkedListNode node)
{
    free(node->data);
    free(node);
}
