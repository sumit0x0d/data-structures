#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#include <doubly-linked-list.h>

struct doubly_linked_list_node {
    DS_Data data;
    DoublyLinkedListNode previous;
    DoublyLinkedListNode next;
};

DS_PRIVATE_API
DoublyLinkedListNode DoublyLinkedListNode_Create(const DS_Data data, DS_Size sData);

DS_PRIVATE_API
void DoublyLinkedListNode_Destroy(DoublyLinkedListNode node);

#endif