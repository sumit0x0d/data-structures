#include <stdlib.h>

#include "doubly-linked-list-node.h"

typedef DoublyLinkedListNode Node;

Node DoublyLinkedListNode_Create(const DS_Data data, DS_Size sData)
{
    Node node = (Node)malloc(sizeof (struct doubly_linked_list_node));
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

DS_Void DoublyLinkedListNode_Destroy(Node node)
{
    free(node->data);
    free(node);
}
