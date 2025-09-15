#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#include <doubly-linked-list.h>

struct doubly_linked_list_node {
    DS_Data data;
    DoublyLinkedListNode previous;
    DoublyLinkedListNode next;
};


DoublyLinkedListNode DoublyLinkedListNode_Create(const DS_Data data, DS_Size sData);


void DoublyLinkedListNode_Destroy(DoublyLinkedListNode node);

#endif