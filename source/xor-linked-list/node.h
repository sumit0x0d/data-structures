#ifndef XOR_LINKED_LIST_NODE_H
#define XOR_LINKED_LIST_NODE_H

#include <xor-linked-list.h>

struct XorLinkedListNode {
   void *data;
   size_t xor;
};

XorLinkedListNode *XorLinkedListNode_Create(const void *data, size_t data_size);
void XorLinkedListNode_Destroy(XorLinkedListNode *this);

#endif
