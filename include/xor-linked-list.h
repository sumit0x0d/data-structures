#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct XorLinkedList * XorLinkedList;
typedef struct XorLinkedListNode * XorLinkedListNode;

DATA_STRUCTURES_API
XorLinkedList XorLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Destroy(XorLinkedList this);

DATA_STRUCTURES_API
DS_Generic XorLinkedList_GetNodeData(XorLinkedListNode node);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushHead(XorLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushTail(XorLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopHead(XorLinkedList this);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopTail(XorLinkedList this);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Insert(XorLinkedList this, DS_Size index, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Remove(XorLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Erase(XorLinkedList this, DS_Size index);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Update(XorLinkedList this, DS_Size index, const DS_Generic data);

#endif