#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct doubly_linked_list * DoublyLinkedList;
typedef struct doubly_linked_list_node * DoublyLinkedListNode;

DS_API
DoublyLinkedList DoublyLinkedList_Create(DS_Size sData);

DS_API
void DoublyLinkedList_Destroy(DoublyLinkedList list);

DS_API
DS_Size DoublyLinkedList_GetSize(DoublyLinkedList list);

DS_API
DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList list);

DS_API
DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList list);

DS_API
DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList list);

DS_API
DS_Data DoublyLinkedListNode_GetData(DoublyLinkedListNode node);

DS_API
void DoublyLinkedList_SetData(DoublyLinkedList list, DoublyLinkedListNode node, const DS_Data data);

DS_API
void DoublyLinkedList_PushHead(DoublyLinkedList list, const DS_Data data);

DS_API
void DoublyLinkedList_PushTail(DoublyLinkedList list, const DS_Data data);

DS_API
void DoublyLinkedList_PopHead(DoublyLinkedList list);

DS_API
void DoublyLinkedList_PopTail(DoublyLinkedList list);

DS_API
void DoublyLinkedList_Remove(DoublyLinkedList list, DoublyLinkedListNode node);

DS_API
void DoublyLinkedList_Traverse(DoublyLinkedList list, DS_FunctionUnary fUnary, DS_Context cUnary);

#endif
