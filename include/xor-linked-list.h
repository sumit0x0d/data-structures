#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct XorLinkedList * XorLinkedList;
typedef struct XorLinkedListNode * XorLinkedListNode;

DATA_STRUCTURES_API
XorLinkedList XorLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Destroy(XorLinkedList self);

DATA_STRUCTURES_API
DS_Generic XorLinkedList_GetNodeData(XorLinkedListNode node);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushHead(XorLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushTail(XorLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopHead(XorLinkedList self);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopTail(XorLinkedList self);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Insert(XorLinkedList self, DS_Size index, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Remove(XorLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Erase(XorLinkedList self, DS_Size index);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Update(XorLinkedList self, DS_Size index, const DS_Generic data);

#endif