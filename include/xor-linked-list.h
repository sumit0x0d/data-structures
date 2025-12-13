#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <stddef.h>

typedef struct XorLinkedList XorLinkedList;
typedef struct XorLinkedListNode XorLinkedListNode;

__attribute__((visibility("default")))
XorLinkedList *XorLinkedList_Create(size_t data_size);

__attribute__((visibility("default")))
void XorLinkedList_Destroy(XorLinkedList *this);

__attribute__((visibility("default")))
void *XorLinkedList_GetNodeData(XorLinkedListNode *node);

__attribute__((visibility("default")))
void XorLinkedList_PushHead(XorLinkedList *this, const void *data);

__attribute__((visibility("default")))
void XorLinkedList_PushTail(XorLinkedList *this, const void *data);

__attribute__((visibility("default")))
void XorLinkedList_PopHead(XorLinkedList *this);

__attribute__((visibility("default")))
void XorLinkedList_PopTail(XorLinkedList *this);

__attribute__((visibility("default")))
void XorLinkedList_Insert(XorLinkedList *this, size_t index, const void *data);

__attribute__((visibility("default")))
void XorLinkedList_Remove(XorLinkedList *this, const void *data);

__attribute__((visibility("default")))
void XorLinkedList_Erase(XorLinkedList *this, size_t index);

__attribute__((visibility("default")))
void XorLinkedList_Update(XorLinkedList *this, size_t index, const void *data);

#endif