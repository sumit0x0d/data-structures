#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_NODE_H

#include <singly-linked-list.h>

struct SinglyLinkedListNode {
   void *data;
   SinglyLinkedListNode *next;
};

SinglyLinkedListNode *SinglyLinkedListNode_Create(const void *data,size_t data_size);
void SinglyLinkedListNode_Destroy(SinglyLinkedListNode *this);

#endif
