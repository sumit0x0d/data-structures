#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct xor_linked_list * XorLinkedList;
typedef struct xor_linked_list_node * XorLinkedListNode;

DS_API
XorLinkedList XorLinkedList_Create(DS_Size sData);

DS_API
void XorLinkedList_Destroy(XorLinkedList list);

DS_API
DS_Data XorLinkedListNode_GetData(XorLinkedListNode node);

DS_API
void XorLinkedList_PushHead(XorLinkedList list, const DS_Data data);

DS_API
void XorLinkedList_PushTail(XorLinkedList list, const DS_Data data);

DS_API
void XorLinkedList_PopHead(XorLinkedList list);

DS_API
void XorLinkedList_PopTail(XorLinkedList list);

DS_API
void XorLinkedList_Insert(XorLinkedList list, DS_Size index, const DS_Data data);

DS_API
void XorLinkedList_Remove(XorLinkedList list, const DS_Data data);

DS_API
void XorLinkedList_Erase(XorLinkedList list, DS_Size index);

DS_API
void XorLinkedList_Update(XorLinkedList list, DS_Size index, const DS_Data data);

#endif