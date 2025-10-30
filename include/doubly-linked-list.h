#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct DoublyLinkedList * DoublyLinkedList;
typedef struct DoublyLinkedListNode * DoublyLinkedListNode;
typedef struct DoublyLinkedListIterator * DoublyLinkedListIterator;

DATA_STRUCTURES_API
DoublyLinkedList DoublyLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_Destroy(DoublyLinkedList this);

DATA_STRUCTURES_API
DS_Size DoublyLinkedList_GetSize(DoublyLinkedList this);

DATA_STRUCTURES_API
DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList this);

DATA_STRUCTURES_API
DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList this);

DATA_STRUCTURES_API
DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList this);

DATA_STRUCTURES_API
DS_Generic DoublyLinkedList_GetNodeData(DoublyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_SetNodeData(DoublyLinkedList this, DoublyLinkedListNode node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PushHead(DoublyLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PushTail(DoublyLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PopHead(DoublyLinkedList this);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_PopTail(DoublyLinkedList this);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_RemoveNode(DoublyLinkedList this, DoublyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void DoublyLinkedList_Traverse(DoublyLinkedList this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DoublyLinkedListIterator DoublyLinkedList_CreateItreator(DoublyLinkedList this);

#endif
