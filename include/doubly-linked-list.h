#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct DoublyLinkedList * DoublyLinkedList;
typedef struct DoublyLinkedListNode * DoublyLinkedListNode;

DS_API
DoublyLinkedList DoublyLinkedList_Create(DS_Size data_size);

DS_API
DS_Void DoublyLinkedList_Destroy(DoublyLinkedList doubly_linked_list);

DS_API
DS_Size DoublyLinkedList_GetSize(DoublyLinkedList doubly_linked_list);

DS_API
DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList doubly_linked_list);

DS_API
DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList doubly_linked_list);

DS_API
DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList doubly_linked_list);

DS_API
DS_Generic DoublyLinkedList_GetData(DoublyLinkedListNode node);

DS_API
DS_Void DoublyLinkedList_SetData(DoublyLinkedList doubly_linked_list,
    DoublyLinkedListNode node, const DS_Generic data);

DS_API
DS_Void DoublyLinkedList_PushHead(DoublyLinkedList doubly_linked_list,
    const DS_Generic data);

DS_API
DS_Void DoublyLinkedList_PushTail(DoublyLinkedList doubly_linked_list,
    const DS_Generic data);

DS_API
DS_Void DoublyLinkedList_PopHead(DoublyLinkedList doubly_linked_list);

DS_API
DS_Void DoublyLinkedList_PopTail(DoublyLinkedList doubly_linked_list);

DS_API
DS_Void DoublyLinkedList_Remove(DoublyLinkedList doubly_linked_list,
    DoublyLinkedListNode node);

DS_API
DS_Void DoublyLinkedList_Traverse(DoublyLinkedList doubly_linked_list,
    DS_CallbackUnary unary_callback, DS_Generic unary_context);

#endif
