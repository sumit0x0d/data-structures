#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct SinglyLinkedList * SinglyLinkedList;
typedef struct SinglyLinkedListNode * SinglyLinkedListNode;

DATA_STRUCTURES_API
SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_Destroy(SinglyLinkedList this);

DATA_STRUCTURES_API
DS_Size SinglyLinkedList_GetSize(SinglyLinkedList this);

DATA_STRUCTURES_API
DS_Size SinglyLinkedList_GetDataSize(SinglyLinkedList this);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetHead(SinglyLinkedList this);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetTail(SinglyLinkedList this);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_SetData(SinglyLinkedList this, SinglyLinkedListNode node, const DS_Generic data);

DATA_STRUCTURES_API
DS_Generic SinglyLinkedList_GetNodeData(SinglyLinkedListNode node);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PushHead(SinglyLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PushTail(SinglyLinkedList this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PopHead(SinglyLinkedList this);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_PopTail(SinglyLinkedList this);

DATA_STRUCTURES_API
DS_Void SinglyLinkedList_Traverse(SinglyLinkedList this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList this);

DATA_STRUCTURES_API
SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList this);

DATA_STRUCTURES_API
SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList this1, SinglyLinkedList this2);

#endif