#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H

#include <singly-linked-list.h>

struct singly_linked_list_node {
    DS_Data data;
    SinglyLinkedListNode next;
};

DS_PRIVATE_API
SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Data data, DS_Size sData);

DS_PRIVATE_API
void SinglyLinkedListNode_Destroy(SinglyLinkedListNode node);

#endif