#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct DoublyLinkedList * DoublyLinkedList;
typedef struct DoublyLinkedListNode * DoublyLinkedListNode;
typedef struct DoublyLinkedListIterator * DoublyLinkedListIterator;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} DoublyLinkedListUnaryCallback;

__attribute__((visibility("default")))
DoublyLinkedList DoublyLinkedList_Create(size_t data_size);

__attribute__((visibility("default")))
void DoublyLinkedList_Destroy(DoublyLinkedList this);

__attribute__((visibility("default")))
size_t DoublyLinkedList_GetSize(DoublyLinkedList this);

__attribute__((visibility("default")))
size_t DoublyLinkedList_GetDataSize(DoublyLinkedList this);

__attribute__((visibility("default")))
DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList this);

__attribute__((visibility("default")))
DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList this);

__attribute__((visibility("default")))
void *DoublyLinkedList_GetNodeData(DoublyLinkedListNode node);

__attribute__((visibility("default")))
void DoublyLinkedList_SetNodeData(DoublyLinkedList this, DoublyLinkedListNode node, const void *data);

__attribute__((visibility("default")))
void DoublyLinkedList_PushHead(DoublyLinkedList this, const void *data);

__attribute__((visibility("default")))
void DoublyLinkedList_PushTail(DoublyLinkedList this, const void *data);

__attribute__((visibility("default")))
void DoublyLinkedList_PopHead(DoublyLinkedList this);

__attribute__((visibility("default")))
void DoublyLinkedList_PopTail(DoublyLinkedList this);

__attribute__((visibility("default")))
void DoublyLinkedList_RemoveNode(DoublyLinkedList this, DoublyLinkedListNode node);

__attribute__((visibility("default")))
void DoublyLinkedList_Traverse(DoublyLinkedList this, DoublyLinkedListUnaryCallback unary_callback);

__attribute__((visibility("default")))
DoublyLinkedListIterator DoublyLinkedList_CreateItreator(DoublyLinkedList this);

#endif
