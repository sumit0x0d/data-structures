#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct doubly_linked_list DoublyLinkedList;
typedef struct doubly_linked_list_node DoublyLinkedListNode;
typedef void (*DoublyLinkedListTraverse)(void *data, void *uData);

DoublyLinkedList *DoublyLinkedList_Create(size_t dSize);
void DoublyLinkedList_Destroy(DoublyLinkedList *dlList);

size_t DoublyLinkedList_GetSize(DoublyLinkedList *dlList);
size_t DoublyLinkedList_GetDataSize(DoublyLinkedList *dlList);
DoublyLinkedListNode *DoublyLinkedList_GetHead(DoublyLinkedList *dlList);
DoublyLinkedListNode *DoublyLinkedList_GetTail(DoublyLinkedList *dlList);
void *DoublyLinkedListNode_GetData(DoublyLinkedListNode *dllNode);

void DoublyLinkedList_SetData(DoublyLinkedList *dlList, DoublyLinkedListNode *dllNode, const void *data);

void DoublyLinkedList_PushHead(DoublyLinkedList *dlList, const void *data);
void DoublyLinkedList_PushTail(DoublyLinkedList *dlList, const void *data);
void DoublyLinkedList_PopHead(DoublyLinkedList *dlList);
void DoublyLinkedList_PopTail(DoublyLinkedList *dlList);

void DoublyLinkedList_Remove(DoublyLinkedList *dlList, DoublyLinkedListNode *dllNode);

void DoublyLinkedList_Traverse(DoublyLinkedList *dlList, DoublyLinkedListTraverse dllTraverse, void *uData);

#endif
