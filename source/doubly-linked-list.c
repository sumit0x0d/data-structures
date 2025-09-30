#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>

#include "doubly-linked-list-node.h"

typedef DoublyLinkedListNode Node;

struct doubly_linked_list {
     Node head;
     Node tail;
     DS_Size data_size;
     DS_Size size;
};

DoublyLinkedList DoublyLinkedList_Create(DS_Size size)
{
     DoublyLinkedList list = (DoublyLinkedList)malloc(sizeof (struct doubly_linked_list));
     if (!list) {
          return NULL;
     }
     list->head = NULL;
     list->tail = NULL;
     list->data_size = size;
     list->size = 0;
     return list;
}

DS_Void DoublyLinkedList_Destroy(DoublyLinkedList list)
{
     Node node = list->head;
     while (node) {
          Node *nnode = node->next;
          DoublyLinkedListNode_Destroy(node);
          node = nnode;
     }
     free(list);
}

DS_Size DoublyLinkedList_GetSize(DoublyLinkedList list)
{
     return list->size;
}

DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList list)
{
     return list->data_size;
}

DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList list)
{
     return list->head;
}

DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList list)
{
     return list->tail;
}

DS_Generic DoublyLinkedListNode_GetData(Node node)
{
     return node->data;
}

DS_Void DoublyLinkedList_set_data(DoublyLinkedList list, Node node, const DS_Generic data)
{
     memcpy(node->data, data, list->data_size);
}

DS_Void DoublyLinkedList_PushHead(DoublyLinkedList list, const DS_Generic data)
{
     Node node = DoublyLinkedListNode_Create(data, list->data_size);
     node->previous = NULL;
     if (list->size) {
          list->head->previous = node;
          node->next = list->head;
     } else {
          list->tail = node;
          node->next = NULL;
     }
     list->head = node;
     list->size++;
}

DS_Void DoublyLinkedList_PushTail(DoublyLinkedList list, const DS_Generic data)
{
     Node node = DoublyLinkedListNode_Create(data, list->data_size);
     node->next = NULL;
     if (list->size) {
          list->tail->next = node;
          node->previous = list->tail;
     } else {
          list->head = node;
          node->previous = NULL;
     }
     list->tail = node;
     list->size++;
}

DS_Void DoublyLinkedList_PopHead(DoublyLinkedList list)
{
     Node node = list->head;
     list->head = list->head->next;
     if (!list->head) {
          list->tail = NULL;
     }
     DoublyLinkedListNode_Destroy(node);
     list->size--;
}

DS_Void DoublyLinkedList_PopTail(DoublyLinkedList list)
{
     Node node = list->tail;
     list->tail = list->tail->previous;
     if (list->tail) {
          list->tail->next = NULL;
     }
     DoublyLinkedListNode_Destroy(node);
     list->size--;
}

DS_Void DoublyLinkedList_Remove(DoublyLinkedList list, Node node)
{
     if (node->previous && node->previous->next == (Node)node) {
          node->previous->next = node->next;
     } else {
          list->head = list->head->next;
     }
     if (node->next && node->next->previous == node) {
          node->next->previous = node->previous;
     } else {
          list->tail = list->tail->previous;
     }
     DoublyLinkedListNode_Destroy(node);
     list->size--;
}

DS_Void DoublyLinkedList_Traverse(DoublyLinkedList list, DS_CallbackUnary unary_callback, DS_Generic unary_context)
{
     Node node = list->head;
     while (node) {
          traverse(node->data, unary_context);
          node = node->next;
     }
}
