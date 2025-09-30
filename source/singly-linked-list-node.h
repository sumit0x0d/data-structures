#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H

#include <singly-linked-list.h>

struct singly_linked_list_node {
    DS_Generic data;
    SinglyLinkedListNode next;
};

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Generic data, DS_Size data_size);

DS_Void SinglyLinkedListNode_Destroy(SinglyLinkedListNode node);

#endif