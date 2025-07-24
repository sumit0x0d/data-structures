#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <stddef.h>

typedef struct xor_linked_list XorLinkedList;
typedef struct xor_linked_list_node XorLinkedListNode;

XorLinkedList *XorLinkedList_Create(size_t dSize);
void XorLinkedList_Destroy(XorLinkedList *xlList);

void *XorLinkedListNode_GetData(XorLinkedListNode *node);

void XorLinkedList_PushHead(XorLinkedList *xlList, const void *data);
void XorLinkedList_PushTail(XorLinkedList *xlList, const void *data);
void XorLinkedList_PopHead(XorLinkedList *xlList);
void XorLinkedList_PopTail(XorLinkedList *xlList);
void XorLinkedList_Insert(XorLinkedList *xlList, size_t index, const void *data);
void XorLinkedList_Remove(XorLinkedList *xlList, const void *data);
void XorLinkedList_Erase(XorLinkedList *xlList, size_t index);
void XorLinkedList_Update(XorLinkedList *xlList, size_t index, const void *data);

#endif
