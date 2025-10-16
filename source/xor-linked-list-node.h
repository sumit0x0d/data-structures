#ifndef XOR_LINKED_LIST_NODE_H
#define XOR_LINKED_LIST_NODE_H

#include <xor-linked-list.h>

struct XorLinkedListNode {
     DS_Generic data;
     DS_Size xor;
};

XorLinkedListNode XorLinkedListNode_Create(
     const DS_Generic data,
     DS_Size          data_size
);

DS_Void XorLinkedListNode_Destroy(
     XorLinkedListNode node
);

#endif