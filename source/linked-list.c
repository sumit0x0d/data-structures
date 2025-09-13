#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <linked-list.h>

#include "linked-list-node.h"

struct linked_list {
     LinkedListNode head;
     LinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

LinkedList LinkedList_Create(DS_Size size)
{
     LinkedList list = (LinkedList )malloc(sizeof (LinkedList));
     assert(list);
     list->head = NULL;
     list->tail = NULL;
     list->data_size = size;
     list->size = 0;
     return list;
}

void LinkedList_Destroy(LinkedList list)
{
     free(list->head);
     free(list);
}

void LinkedList_PushHead(LinkedList list, const DS_Data data)
{
     LinkedListNode node = LinkedListNode_Create(data, list->data_size);
     if (list->size) {
          node->next = list->head;
     } else {
          node->next = NULL;
          list->tail = node;
     }
     list->head = node;
     list->size++;
}

void LinkedList_PushTail(LinkedList list, const DS_Data data)
{
     LinkedListNode node = LinkedListNode_Create(data, list->data_size);
     node->next = NULL;
     if (list->size) {
          list->tail->next = node;
     } else {
          list->head = node;
     }
     list->tail = node;
     list->size++;
}

void LinkedList_PopHead(LinkedList list)
{
     LinkedListNode node = list->head;
     list->head = list->head->next;
     if (!list->head) {
          list->tail = NULL;
     }
     LinkedListNode_Destroy(node);
     list->size--;
}

void LinkedList_PopTail(LinkedList list)
{
     if (list->head == list->tail) {
          free(list->head);
          list->head = NULL;
          list->tail = NULL;
          return;
     }
     LinkedListNode node = list->head;
     while (node->next != list->tail) {
          node = node->next;
     }
     node->next = NULL;
     free(list->tail);
     list->tail = node;
     list->size--;
}

void LinkedList_Traverse(LinkedList list, DS_FunctionTraverse fTraverse, DS_Context context)
{
     LinkedListNode node = list->head;
     while (node) {
          traverse(node->data, context);
          node = node->next;
     }
}

void *LinkedListNode_GetData(LinkedListNode node)
{
     return node->data;
}

void LinkedList_SetData(LinkedList list, LinkedListNode node, const DS_Data data)
{
     memcpy(node->data, data, list->size);
}

LinkedListNode LinkedList_DetectCycle(LinkedList list)
{
     LinkedListNode nTortoise = list->head;
     LinkedListNode nHare = list->head;
     while (nHare && nHare->next) {
          if (nTortoise == nHare) {
               return nTortoise;
          }
          nTortoise = nTortoise->next;
          nHare = nHare->next->next;
     }
     return NULL;
}

LinkedListNode LinkedList_GetMiddleNode(LinkedList list)
{
     LinkedListNode nTortoise = list->head;
     LinkedListNode nHare = list->head;
     while (nHare && nHare->next) {
          nTortoise = nTortoise->next;
          nHare = nHare->next->next;
     }
     return nTortoise;
}

LinkedList LinkedList_MergeSorted(LinkedList list1, LinkedList list2)
{
     LinkedList list = LinkedList_Create(list1->data_size);
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
     LinkedListNode node = list->head;
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
     LinkedList_Destroy(list1);
     LinkedList_Destroy(list2);
     return list;
}
