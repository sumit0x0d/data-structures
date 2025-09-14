#include "singly-linked-list-node.h"

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Data data, DS_Size sData)
{
    SinglyLinkedListNode node = (SinglyLinkedListNode)malloc(sizeof (struct singly_linked_list_node));
    if (!node) {
        return NULL;
    }
    node->data = malloc(sData);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, sData);
    return node;
}

void SinglyLinkedListNode_Destroy(SinglyLinkedListNode node)
{
    free(node->data);
    free(node);
}
