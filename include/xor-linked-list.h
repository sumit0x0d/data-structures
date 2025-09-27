#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct xor_linked_list * XorLinkedList;
typedef struct xor_linked_list_node * XorLinkedListNode;

DS_API
XorLinkedList XorLinkedList_Create(DS_Size data_size);

DS_API
DS_Void XorLinkedList_Destroy(XorLinkedList list);

DS_API
DS_Data XorLinkedListNode_GetData(XorLinkedListNode node);

DS_API
DS_Void XorLinkedList_PushHead(XorLinkedList list, const DS_Data data);

DS_API
DS_Void XorLinkedList_PushTail(XorLinkedList list, const DS_Data data);

DS_API
DS_Void XorLinkedList_PopHead(XorLinkedList list);

DS_API
DS_Void XorLinkedList_PopTail(XorLinkedList list);

DS_API
DS_Void XorLinkedList_Insert(XorLinkedList list, DS_Size index, const DS_Data data);

DS_API
DS_Void XorLinkedList_Remove(XorLinkedList list, const DS_Data data);

DS_API
DS_Void XorLinkedList_Erase(XorLinkedList list, DS_Size index);

DS_API
DS_Void XorLinkedList_Update(XorLinkedList list, DS_Size index, const DS_Data data);

#endif