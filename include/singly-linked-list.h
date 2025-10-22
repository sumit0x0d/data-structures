#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <data-structures.h>

typedef struct SinglyLinkedList * SinglyLinkedList;
typedef struct SinglyLinkedListNode * SinglyLinkedListNode;

DATA_STRUCTURES_API
SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_Destroy(SinglyLinkedList self);

DATA_STRUCTURES_API
DS_Size SinglyLinkedList_GetSize(SinglyLinkedList self);

DATA_STRUCTURES_API
DS_Size SinglyLinkedList_GetDataSize(SinglyLinkedList self);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetHead(SinglyLinkedList self);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetTail(SinglyLinkedList self);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_SetData(SinglyLinkedList self, SinglyLinkedListNode node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Generic SinglyLinkedList_GetNodeData(SinglyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PushHead(SinglyLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PushTail(SinglyLinkedList self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PopHead(SinglyLinkedList self);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PopTail(SinglyLinkedList self);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_Traverse(SinglyLinkedList self, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList self);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList self);

DATA_STRUCTURES_API
SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList self1, SinglyLinkedList self2);

#endif