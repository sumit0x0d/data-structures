#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include <linked-list.h>

struct linked_list_node {
    DS_Data data;
    LinkedListNode next;
};

DS_PRIVATE_API
LinkedListNode LinkedListNode_Create(const DS_Data data, DS_Size sData);

DS_PRIVATE_API
void LinkedListNode_Destroy(LinkedListNode node);

#endif