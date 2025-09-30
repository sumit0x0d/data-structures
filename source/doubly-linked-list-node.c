#include <stdlib.h>

#include "doubly-linked-list-node.h"

typedef DoublyLinkedListNode Node;

Node DoublyLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
    Node node = (Node)malloc(sizeof (struct doubly_linked_list_node));
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

DS_Void DoublyLinkedListNode_Destroy(Node node)
{
    free(node->data);
    free(node);
}
