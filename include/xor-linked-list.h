#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct xor_linked_list XorLinkedList;
typedef struct xor_linked_list_node XorLinkedListNode;

DS_PUBLIC_API
XorLinkedList *DS_XorLinkedList_Create(DS_Size size);

DS_PUBLIC_API
void DS_XorLinkedList_Destroy(XorLinkedList *list);

DS_PUBLIC_API
void *XorLinkedListNode_GetData(XorLinkedListNode *node);

DS_PUBLIC_API
void DS_XorLinkedList_PushHead(XorLinkedList *list, const DS_Data data);

DS_PUBLIC_API
void DS_XorLinkedList_PushTail(XorLinkedList *list, const DS_Data data);

DS_PUBLIC_API
void DS_XorLinkedList_PopHead(XorLinkedList *list);

DS_PUBLIC_API
void DS_XorLinkedList_PopTail(XorLinkedList *list);

DS_PUBLIC_API
void DS_XorLinkedList_Insert(XorLinkedList *list, DS_Size index, const DS_Data data);

DS_PUBLIC_API
void DS_XorLinkedList_Remove(XorLinkedList *list, const DS_Data data);

DS_PUBLIC_API
void DS_XorLinkedList_Erase(XorLinkedList *list, DS_Size index);

DS_PUBLIC_API
void DS_XorLinkedList_Update(XorLinkedList *list, DS_Size index, const DS_Data data);

#endif