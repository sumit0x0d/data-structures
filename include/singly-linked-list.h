#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include <data-structures.h>

typedef struct SinglyLinkedList * SinglyLinkedList;
typedef struct SinglyLinkedListNode * SinglyLinkedListNode;

DS_API
SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size);

DS_API
DS_Void SinglyLinkedList_Destroy(SinglyLinkedList singly_linked_list);

DS_API
DS_Size SinglyLinkedList_GetSize(SinglyLinkedList singly_linked_list);

DS_API
DS_Size SinglyLinkedList_GetDataSize(SinglyLinkedList singly_linked_list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetHeadNode(SinglyLinkedList singly_linked_list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetTailNode(SinglyLinkedList singly_linked_list);

DS_API
DS_Void SinglyLinkedList_SetData(SinglyLinkedList singly_linked_list,
          SinglyLinkedListNode node, const DS_Generic data);

DS_API
DS_Generic SinglyLinkedList_GetNodeData(SinglyLinkedListNode node);

DS_API
DS_Void SinglyLinkedList_PushHead(SinglyLinkedList singly_linked_list,
          const DS_Generic data);

DS_API
DS_Void SinglyLinkedList_PushTail(SinglyLinkedList singly_linked_list,
          const DS_Generic data);

DS_API
DS_Void SinglyLinkedList_PopHead(SinglyLinkedList singly_linked_list);

DS_API
DS_Void SinglyLinkedList_PopTail(SinglyLinkedList singly_linked_list);

DS_API
DS_Void SinglyLinkedList_Traverse(SinglyLinkedList singly_linked_list,
          DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList singly_linked_list);

DS_API
SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList singly_linked_list);

DS_API
SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList singly_linked_list1,
                    SinglyLinkedList singly_linked_list2);

#endif