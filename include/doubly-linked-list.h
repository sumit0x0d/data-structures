#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct doubly_linked_list DoublyLinkedList;
typedef struct doubly_linked_list_node DoublyLinkedListNode;

DS_PUBLIC_API
DoublyLinkedList *DS_DoublyLinkedList_Create(DS_Size sData);
DS_PUBLIC_API
void DS_DoublyLinkedList_Destroy(DoublyLinkedList *list);

DS_PUBLIC_API
DS_Size DS_DoublyLinkedList_GetSize(DoublyLinkedList *list);
DS_PUBLIC_API
DS_Size DS_DoublyLinkedList_GetDataSize(DoublyLinkedList *list);
DS_PUBLIC_API
DoublyLinkedListNode *DS_DoublyLinkedList_GetHead(DoublyLinkedList *list);
DS_PUBLIC_API
DoublyLinkedListNode *DS_DoublyLinkedList_GetTail(DoublyLinkedList *list);
DS_PUBLIC_API
void *DoublyLinkedListNode_GetData(DoublyLinkedListNode *node);

DS_PUBLIC_API
void DS_DoublyLinkedList_SetData(DoublyLinkedList *list, DoublyLinkedListNode *node, const DS_Data data);

DS_PUBLIC_API
DS_DoublyLinkedList_PushHead(DoublyLinkedList *list, const DS_Data data);
DS_PUBLIC_API
DS_DoublyLinkedList_PushTail(DoublyLinkedList *list, const DS_Data data);
DS_PUBLIC_API
DS_DoublyLinkedList_PopHead(DoublyLinkedList *list);
DS_PUBLIC_API
DS_DoublyLinkedList_PopTail(DoublyLinkedList *list);

DS_PUBLIC_API
void DS_DoublyLinkedList_Remove(DoublyLinkedList *list, DoublyLinkedListNode *node);

DS_PUBLIC_API
void DS_DoublyLinkedList_Traverse(DoublyLinkedList *list, DS_FunctionTraverse fTraverse, DS_Data dTemporary);

#endif
