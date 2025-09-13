#include "linked-list-node.h"

typedef LinkedListNode Node;

LinkedListNode LinkedListNode_Create(const DS_Data data, DS_Size sData)
{
    LinkedListNode node = (LinkedListNode)malloc(sizeof (struct linked_list_node));
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

void LinkedListNode_Destroy(LinkedListNode node)
{
    free(node->data);
    free(node);
}
