#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include <data-structures.h>

typedef struct singly_linked_list * SinglyLinkedList;
typedef struct singly_linked_list_node * SinglyLinkedListNode;

DS_API
SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size);

DS_API
DS_Void SinglyLinkedList_Destroy(SinglyLinkedList list);

DS_API
DS_Size SinglyLinkedList_GetSize(SinglyLinkedList list);

DS_API
DS_Size SinglyLinkedList_GetDataSize(SinglyLinkedList list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetHeadNode(SinglyLinkedList list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetTailNode(SinglyLinkedList list);

DS_API
DS_Void SinglyLinkedList_SetData(SinglyLinkedList list, SinglyLinkedListNode node, const DS_Data data);

DS_API
DS_Data SinglyLinkedList_GetNodeData(SinglyLinkedListNode node);

DS_API
DS_Void SinglyLinkedList_PushHead(SinglyLinkedList list, const DS_Data data);

DS_API
DS_Void SinglyLinkedList_PushTail(SinglyLinkedList list, const DS_Data data);

DS_API
DS_Void SinglyLinkedList_PopHead(SinglyLinkedList list);

DS_API
DS_Void SinglyLinkedList_PopTail(SinglyLinkedList list);

DS_API
DS_Void SinglyLinkedList_Traverse(SinglyLinkedList list, DS_FunctionUnary unary_function, DS_Context unary_context);

DS_API
SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList list);

DS_API
SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList list1, SinglyLinkedList list2);

#endif