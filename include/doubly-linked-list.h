#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct DoublyLinkedList * DoublyLinkedList;
typedef struct DoublyLinkedListNode * DoublyLinkedListNode;
typedef struct DoublyLinkedListIterator * DoublyLinkedListIterator;

DATA_STRUCTURES_API
DoublyLinkedList DoublyLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_Destroy(DoublyLinkedList self);

DATA_STRUCTURES_API
DS_Size DoublyLinkedList_GetSize(DoublyLinkedList self);

DATA_STRUCTURES_API
DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList self);

DATA_STRUCTURES_API
DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList self);

DATA_STRUCTURES_API
DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList self);

DATA_STRUCTURES_API
DS_Generic DoublyLinkedList_GetNodeData(DoublyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_SetNodeData(DoublyLinkedList self, DoublyLinkedListNode node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PushHead(DoublyLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PushTail(DoublyLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PopHead(DoublyLinkedList self);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PopTail(DoublyLinkedList self);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_RemoveNode(DoublyLinkedList self, DoublyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_Traverse(DoublyLinkedList self, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DoublyLinkedListIterator DoublyLinkedList_CreateItreator(DoublyLinkedList self);

#endif
