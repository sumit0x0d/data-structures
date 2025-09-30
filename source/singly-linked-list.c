#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <singly-linked-list.h>

#include "singly-linked-list-node.h"

struct singly_linked_list {
     SinglyLinkedListNode head;
     SinglyLinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size)
{
     SinglyLinkedList list = (SinglyLinkedList )malloc(sizeof (SinglyLinkedList));
     assert(list);
     list->head = NULL;
     list->tail = NULL;
     list->data_size = data_size;
     list->size = 0;
     return list;
}

DS_Void SinglyLinkedList_Destroy(SinglyLinkedList list)
{
     free(list->head);
     free(list);
}

DS_Void SinglyLinkedList_PushHead(SinglyLinkedList list, const DS_Generic data)
{
     SinglyLinkedListNode node = SinglyLinkedListNode_Create(data, list->data_size);
     if (list->size) {
          node->next = list->head;
     } else {
          node->next = NULL;
          list->tail = node;
     }
     list->head = node;
     list->size++;
}

DS_Void SinglyLinkedList_PushTail(SinglyLinkedList list, const DS_Generic data)
{
     SinglyLinkedListNode node = SinglyLinkedListNode_Create(data, list->data_size);
     node->next = NULL;
     if (list->size) {
          list->tail->next = node;
     } else {
          list->head = node;
     }
     list->tail = node;
     list->size++;
}

DS_Void SinglyLinkedList_PopHead(SinglyLinkedList list)
{
     SinglyLinkedListNode node = list->head;
     list->head = list->head->next;
     if (!list->head) {
          list->tail = NULL;
     }
     SinglyLinkedListNode_Destroy(node);
     list->size--;
}

DS_Void SinglyLinkedList_PopTail(SinglyLinkedList list)
{
     if (list->head == list->tail) {
          free(list->head);
          list->head = NULL;
          list->tail = NULL;
          return;
     }
     SinglyLinkedListNode node = list->head;
     while (node->next != list->tail) {
          node = node->next;
     }
     node->next = NULL;
     free(list->tail);
     list->tail = node;
     list->size--;
}

DS_Void SinglyLinkedList_Traverse(SinglyLinkedList list, DS_CallbackUnary unary_callback, DS_Generic context)
{
     SinglyLinkedListNode node = list->head;
     while (node) {
          traverse(node->data, context);
          node = node->next;
     }
}

DS_Void *SinglyLinkedListNode_GetData(SinglyLinkedListNode node)
{
     return node->data;
}

DS_Void SinglyLinkedList_SetData(SinglyLinkedList list, SinglyLinkedListNode node, const DS_Generic data)
{
     memcpy(node->data, data, list->data_size);
}

SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList list)
{
     SinglyLinkedListNode nTortoise = list->head;
     SinglyLinkedListNode nHare = list->head;
     while (nHare && nHare->next) {
          if (nTortoise == nHare) {
               return nTortoise;
          }
          nTortoise = nTortoise->next;
          nHare = nHare->next->next;
     }
     return NULL;
}

SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList list)
{
     SinglyLinkedListNode nTortoise = list->head;
     SinglyLinkedListNode nHare = list->head;
     while (nHare && nHare->next) {
          nTortoise = nTortoise->next;
          nHare = nHare->next->next;
     }
     return nTortoise;
}

SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList list1, SinglyLinkedList list2)
{
     SinglyLinkedList list = SinglyLinkedList_Create(list1->data_size);
     if (list1->head->data <= list2->head->data) {
          list->head = list1->head;
          list1->head = list1->head->next;
     } else {
          list->head = list2->head;
          list2->head = list2->head->next;
     }
     if (list1->tail->data <= list2->tail->data) {
          list->tail = list2->tail;
     } else {
          list->tail = list1->tail;
     }
     SinglyLinkedListNode node = list->head;
     while (list1->head && list2->head) {
          if (list1->head->data <= list2->head->data) {
               node->next = list1->head;
               list1->head = list1->head->next;
          } else {
               node->next = list2->head;
               list2->head = list2->head->next;
          }
          node = node->next;
     }
     list->size = list1->size + list2->size;
     SinglyLinkedList_Destroy(list1);
     SinglyLinkedList_Destroy(list2);
     return list;
}
