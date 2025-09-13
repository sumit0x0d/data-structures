#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include <data-structures.h>

typedef struct linked_list * LinkedList;
typedef struct linked_list_node * LinkedListNode;

DS_PUBLIC_API
LinkedList LinkedList_Create(DS_Size size);

DS_PUBLIC_API
void LinkedList_Destroy(LinkedList list);

DS_PUBLIC_API
DS_Size LinkedList_GetSize(LinkedList list);

DS_PUBLIC_API
DS_Size LinkedList_GetDataSize(LinkedList list);

DS_PUBLIC_API
LinkedListNode LinkedList_GetHeadNode(LinkedList list);

DS_PUBLIC_API
LinkedListNode LinkedList_GetTailNode(LinkedList list);

DS_PUBLIC_API
void LinkedList_SetData(LinkedList list, LinkedListNode node, const DS_Data data);

DS_PUBLIC_API
DS_Data LinkedListNode_GetData(LinkedListNode node);

DS_PUBLIC_API
void LinkedList_PushHead(LinkedList list, const DS_Data data);

DS_PUBLIC_API
void LinkedList_PushTail(LinkedList list, const DS_Data data);

DS_PUBLIC_API
void LinkedList_PopHead(LinkedList list);

DS_PUBLIC_API
void LinkedList_PopTail(LinkedList list);

DS_PUBLIC_API
void LinkedList_Traverse(LinkedList list, DS_FunctionTraverse fTraverse, DS_Context context);

DS_PUBLIC_API
LinkedListNode LinkedList_DetectCycle(LinkedList list);

DS_PUBLIC_API
LinkedListNode LinkedList_GetMiddleNode(LinkedList list);

DS_PUBLIC_API
LinkedList LinkedList_MergeSorted(LinkedList list1, LinkedList list2);

#endif