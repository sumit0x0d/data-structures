#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <singly-linked-list.h>

#include "singly-linked-list-node.h"

struct SinglyLinkedList {
     SinglyLinkedListNode head;
     SinglyLinkedListNode tail;
     DS_Size              data_size;
     DS_Size              size;
};

SinglyLinkedList SinglyLinkedList_Create(
     DS_Size data_size
) {
     SinglyLinkedList singly_linked_list =
          (SinglyLinkedList)malloc(sizeof (struct SinglyLinkedList));
     if (!singly_linked_list) {
          return NULL;
     }
     singly_linked_list->head = NULL;
     singly_linked_list->tail = NULL;
     singly_linked_list->data_size = data_size;
     singly_linked_list->size = 0;
     return singly_linked_list;
}

DS_Void SinglyLinkedList_Destroy(
     SinglyLinkedList singly_linked_list
) {
     free(singly_linked_list->head);
     free(singly_linked_list);
}

DS_Void SinglyLinkedList_PushHead(
     SinglyLinkedList singly_linked_list,
     const DS_Generic data
) {
     SinglyLinkedListNode node =
          SinglyLinkedListNode_Create(data, singly_linked_list->data_size);
     if (singly_linked_list->size) {
          node->next = singly_linked_list->head;
     } else {
          node->next = NULL;
          singly_linked_list->tail = node;
     }
     singly_linked_list->head = node;
     singly_linked_list->size++;
}

DS_Void SinglyLinkedList_PushTail(
     SinglyLinkedList singly_linked_list,
     const DS_Generic data
) {
     SinglyLinkedListNode node =
          SinglyLinkedListNode_Create(data, singly_linked_list->data_size);
     node->next = NULL;
     if (singly_linked_list->size) {
          singly_linked_list->tail->next = node;
     } else {
          singly_linked_list->head = node;
     }
     singly_linked_list->tail = node;
     singly_linked_list->size++;
}

DS_Void SinglyLinkedList_PopHead(
     SinglyLinkedList singly_linked_list
) {
     SinglyLinkedListNode node = singly_linked_list->head;
     singly_linked_list->head = singly_linked_list->head->next;
     if (!singly_linked_list->head) {
          singly_linked_list->tail = NULL;
     }
     SinglyLinkedListNode_Destroy(node);
     singly_linked_list->size--;
}

DS_Void SinglyLinkedList_PopTail(
     SinglyLinkedList singly_linked_list
) {
     if (singly_linked_list->head == singly_linked_list->tail) {
          free(singly_linked_list->head);
          singly_linked_list->head = NULL;
          singly_linked_list->tail = NULL;
          return;
     }
     SinglyLinkedListNode node = singly_linked_list->head;
     while (node->next != singly_linked_list->tail) {
          node = node->next;
     }
     node->next = NULL;
     free(singly_linked_list->tail);
     singly_linked_list->tail = node;
     singly_linked_list->size--;
}

DS_Void SinglyLinkedList_Traverse(
     SinglyLinkedList singly_linked_list,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
) {
     SinglyLinkedListNode node = singly_linked_list->head;
     while (node) {
          unary_callback(node->data, unary_context);
          node = node->next;
     }
}

DS_Generic SinglyLinkedListNode_GetData(
     SinglyLinkedListNode node
) {
     return node->data;
}

DS_Void SinglyLinkedList_SetData(
     SinglyLinkedList     singly_linked_list,
     SinglyLinkedListNode node,
     const DS_Generic     data
) {
     memcpy(node->data, data, singly_linked_list->data_size);
}

SinglyLinkedListNode SinglyLinkedList_DetectCycle(
     SinglyLinkedList singly_linked_list
) {
     SinglyLinkedListNode nTortoise = singly_linked_list->head;
     SinglyLinkedListNode nHare = singly_linked_list->head;
     while (nHare && nHare->next) {
          if (nTortoise == nHare) {
               return nTortoise;
          }
          nTortoise = nTortoise->next;
          nHare = nHare->next->next;
     }
     return NULL;
}

SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(
     SinglyLinkedList singly_linked_list
) {
     SinglyLinkedListNode tortoise = singly_linked_list->head;
     SinglyLinkedListNode hare = singly_linked_list->head;
     while (hare && hare->next) {
          tortoise = tortoise->next;
          hare = hare->next->next;
     }
     return tortoise;
}

SinglyLinkedList SinglyLinkedList_MergeSorted(
     SinglyLinkedList singly_linked_list1,
     SinglyLinkedList singly_linked_list2
) {
     SinglyLinkedList singly_linked_list =
          SinglyLinkedList_Create(singly_linked_list1->data_size);
     if (singly_linked_list1->head->data <= singly_linked_list2->head->data) {
          singly_linked_list->head = singly_linked_list1->head;
          singly_linked_list1->head = singly_linked_list1->head->next;
     } else {
          singly_linked_list->head = singly_linked_list2->head;
          singly_linked_list2->head = singly_linked_list2->head->next;
     }
     if (singly_linked_list1->tail->data <= singly_linked_list2->tail->data) {
          singly_linked_list->tail = singly_linked_list2->tail;
     } else {
          singly_linked_list->tail = singly_linked_list1->tail;
     }
     SinglyLinkedListNode node = singly_linked_list->head;
     while (singly_linked_list1->head && singly_linked_list2->head) {
          if (singly_linked_list1->head->data <= singly_linked_list2->head->data) {
               node->next = singly_linked_list1->head;
               singly_linked_list1->head = singly_linked_list1->head->next;
          } else {
               node->next = singly_linked_list2->head;
               singly_linked_list2->head = singly_linked_list2->head->next;
          }
          node = node->next;
     }
     singly_linked_list->size = singly_linked_list1->size + singly_linked_list2->size;
     SinglyLinkedList_Destroy(singly_linked_list1);
     SinglyLinkedList_Destroy(singly_linked_list2);
     return singly_linked_list;
}
