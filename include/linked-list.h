#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct linked_list LinkedList;
typedef struct linked_list_node LinkedListNode;
typedef void (*LinkedListTraverse)(void *data, void *uData);

LinkedList *LinkedList_Create(size_t dSize);
void LinkedList_Destroy(LinkedList *lList);

size_t LinkedList_GetSize(LinkedList *lList);
size_t LinkedList_GetDataSize(LinkedList *lList);
LinkedListNode *LinkedList_GetHead(LinkedList *lList);
LinkedListNode *LinkedList_GetTail(LinkedList *lList);

void LinkedList_SetData(LinkedList *lList, LinkedListNode *node, const void *data);
void *LinkedListNode_GetData(LinkedListNode *node);

void LinkedList_PushHead(LinkedList *lList, const void *data);
void LinkedList_PushTail(LinkedList *lList, const void *data);
void LinkedList_PopHead(LinkedList *lList);
void LinkedList_PopTail(LinkedList *lList);

void LinkedList_Traverse(LinkedList *lList, LinkedListTraverse llTraverse, void *uData);

LinkedListNode *LinkedList_Detect_Cycle(LinkedList *lList);
LinkedListNode *LinkedList_GetMiddleNode(LinkedList *lList);
LinkedList *LinkedList_MergeSorted(LinkedList *lList1, LinkedList *lList2);

#endif
