#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef struct SinglyLinkedList SinglyLinkedList;
typedef struct SinglyLinkedListNode SinglyLinkedListNode;

typedef struct {
   void (*function)(void *data, void *user_data);
   void *user_data;
} SinglyLinkedListUnaryCallback;

__attribute__((visibility("default")))
SinglyLinkedList *SinglyLinkedList_Create(size_t data_size);

__attribute__((visibility("default")))
void SinglyLinkedList_Destroy(SinglyLinkedList *this);

__attribute__((visibility("default")))
size_t SinglyLinkedList_GetSize(SinglyLinkedList *this);

__attribute__((visibility("default")))
size_t SinglyLinkedList_GetDataSize(SinglyLinkedList *this);

__attribute__((visibility("default")))
SinglyLinkedListNode *SinglyLinkedList_GetHead(SinglyLinkedList *this);

__attribute__((visibility("default")))
SinglyLinkedListNode *SinglyLinkedList_GetTail(SinglyLinkedList *this);

__attribute__((visibility("default")))
void SinglyLinkedList_SetData(SinglyLinkedList *this,
   SinglyLinkedListNode *node, const void *data);

__attribute__((visibility("default")))
void *SinglyLinkedList_GetNodeData(SinglyLinkedListNode *node);

__attribute__((visibility("default")))
void SinglyLinkedList_PushHead(SinglyLinkedList *this, const void *data);

__attribute__((visibility("default")))
void SinglyLinkedList_PushTail(SinglyLinkedList *this, const void *data);

__attribute__((visibility("default")))
void SinglyLinkedList_PopHead(SinglyLinkedList *this);

__attribute__((visibility("default")))
void SinglyLinkedList_PopTail(SinglyLinkedList *this);

__attribute__((visibility("default")))
void SinglyLinkedList_Traverse(SinglyLinkedList *this,
   SinglyLinkedListUnaryCallback unary_callback);

__attribute__((visibility("default")))
SinglyLinkedListNode *SinglyLinkedList_DetectCycle(SinglyLinkedList *this);

__attribute__((visibility("default")))
SinglyLinkedListNode *inglyLinkedList_GetMiddleNode(SinglyLinkedList *this);

__attribute__((visibility("default")))
SinglyLinkedList *SinglyLinkedList_MergeSorted(SinglyLinkedList *this1,
   SinglyLinkedList *this2);

#endif
