#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include <data-structures.h>

typedef struct linked_list LinkedList;
typedef struct linked_list_node LinkedListNode;

DS_PUBLIC_API
LinkedList *DS_LinkedList_Create(DS_Size size);

DS_PUBLIC_API
void DS_LinkedList_Destroy(LinkedList *list);

DS_PUBLIC_API
DS_Size DS_LinkedList_GetSize(LinkedList *list);

DS_PUBLIC_API
DS_Size DS_LinkedList_GetDataSize(LinkedList *list);

DS_PUBLIC_API
LinkedListNode *DS_LinkedList_GetHead(LinkedList *list);

DS_PUBLIC_API
LinkedListNode *DS_LinkedList_GetTail(LinkedList *list);

DS_PUBLIC_API
void DS_LinkedList_SetData(LinkedList *list, LinkedListNode *node, const DS_Data data);

DS_PUBLIC_API
void *LinkedListNode_GetData(LinkedListNode *node);

DS_PUBLIC_API
void DS_LinkedList_PushHead(LinkedList *list, const DS_Data data);

DS_PUBLIC_API
void DS_LinkedList_PushTail(LinkedList *list, const DS_Data data);

DS_PUBLIC_API
void DS_LinkedList_PopHead(LinkedList *list);

DS_PUBLIC_API
void DS_LinkedList_PopTail(LinkedList *list);

DS_PUBLIC_API
void DS_LinkedList_Traverse(LinkedList *list, DS_FunctionTraverse fTraverse, void *uData);

DS_PUBLIC_API
LinkedListNode *DS_LinkedList_Detect_Cycle(LinkedList *list);

DS_PUBLIC_API
LinkedListNode *DS_LinkedList_GetMiddleNode(LinkedList *list);

DS_PUBLIC_API
LinkedList *DS_LinkedList_MergeSorted(LinkedList *list1, LinkedList *list2);

#endif