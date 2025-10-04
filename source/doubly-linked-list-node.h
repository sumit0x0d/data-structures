#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#include <doubly-linked-list.h>

struct DoublyLinkedListNode {
     DS_Generic data;
     DoublyLinkedListNode previous;
     DoublyLinkedListNode next;
};

DoublyLinkedListNode DoublyLinkedListNode_Create(const DS_Generic data,
                         DS_Size data_size);

DS_Void DoublyLinkedListNode_Destroy(DoublyLinkedListNode node);

#endif