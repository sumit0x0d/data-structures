#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#include <doubly-linked-list.h>

struct DoublyLinkedListNode {
     void *data;
     DoublyLinkedListNode *previous;
     DoublyLinkedListNode *next;
};

DoublyLinkedListNode *DoublyLinkedListNode_Create(const void *data, size_t data_size);
void DoublyLinkedListNode_Destroy(DoublyLinkedListNode *this);

#endif