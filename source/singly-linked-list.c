#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <singly-linked-list.h>

#include "singly-linked-list-node.h"

struct SinglyLinkedList {
     SinglyLinkedListNode head;
     SinglyLinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

SinglyLinkedList SinglyLinkedList_Create(DS_Size data_size)
{
     SinglyLinkedList self;

     self = (SinglyLinkedList)malloc(sizeof (struct SinglyLinkedList));
     if (!self) {
          return NULL;
     }
     
     self->head = NULL;
     self->tail = NULL;
     self->data_size = data_size;
     self->size = 0;
     
     return self;
}

DS_Void SinglyLinkedList_Destroy(SinglyLinkedList self)
{
     free(self->head);
     free(self);
}

DS_Void SinglyLinkedList_PushHead(SinglyLinkedList self, const DS_Generic data)
{
     SinglyLinkedListNode node;
     
     node = SinglyLinkedListNode_Create(data, self->data_size);
     
     if (self->size) {
          node->next = self->head;
     } else {
          node->next = NULL;
          self->tail = node;
     }
     
     self->head = node;
     self->size++;
}

DS_Void SinglyLinkedList_PushTail(SinglyLinkedList self, const DS_Generic data)
{
     SinglyLinkedListNode node;

     node = SinglyLinkedListNode_Create(data, self->data_size);
     node->next = NULL;

     if (self->size) {
          self->tail->next = node;
     } else {
          self->head = node;
     }

     self->tail = node;
     self->size++;
}

DS_Void SinglyLinkedList_PopHead(SinglyLinkedList self)
{
     SinglyLinkedListNode node;

     node = self->head;
     
     self->head = self->head->next;
     if (!self->head) {
          self->tail = NULL;
     }
     
     SinglyLinkedListNode_Destroy(node);
     self->size--;
}

DS_Void SinglyLinkedList_PopTail(SinglyLinkedList self)
{
     SinglyLinkedListNode node;
     
     if (self->size == 0) {
          return;
     }
     
     if (self->head == self->tail) {
          free(self->head);
          self->head = NULL;
          self->tail = NULL;
          return;
     }
     
     node = self->head;
     
     while (node->next != self->tail) {
          node = node->next;
     }
     
     node->next = NULL;
     free(self->tail);
     self->tail = node;
     self->size--;
}

DS_Void SinglyLinkedList_Traverse(SinglyLinkedList self, DS_UnaryCallback unary_callback)
{
     SinglyLinkedListNode node;

     node = self->head;
     while (node) {
          unary_callback.function(node->data, unary_callback.context);
          node = node->next;
     }
}

DS_Generic SinglyLinkedListNode_GetData(SinglyLinkedListNode node)
{
     return node->data;
}

DS_Void SinglyLinkedList_SetData(SinglyLinkedList self, SinglyLinkedListNode node, const DS_Generic data)
{
     memcpy(node->data, data, self->data_size);
}

SinglyLinkedListNode SinglyLinkedList_DetectCycle(SinglyLinkedList self)
{
     SinglyLinkedListNode tortoise;
     SinglyLinkedListNode hare;

     tortoise = self->head;
     
     hare = self->head;
     while (hare && hare->next) {
          if (tortoise == hare) {
               return tortoise;
          }
          tortoise = tortoise->next;
          hare = hare->next->next;
     }
     
     return NULL;
}

SinglyLinkedListNode SinglyLinkedList_GetMiddleNode(SinglyLinkedList self)
{
     SinglyLinkedListNode tortoise;
     SinglyLinkedListNode hare;

     tortoise = self->head;
     
     hare = self->head;
     while (hare && hare->next) {
          tortoise = tortoise->next;
          hare = hare->next->next;
     }

     return tortoise;
}

SinglyLinkedList SinglyLinkedList_MergeSorted(SinglyLinkedList self1, SinglyLinkedList self2)
{
     SinglyLinkedList self;
     SinglyLinkedListNode node;

     self = SinglyLinkedList_Create(self1->data_size);

     if (self1->head->data <= self2->head->data) {
          self->head = self1->head;
          self1->head = self1->head->next;
     } else {
          self->head = self2->head;
          self2->head = self2->head->next;
     }

     if (self1->tail->data <= self2->tail->data) {
          self->tail = self2->tail;
     } else {
          self->tail = self1->tail;
     }

     node = self->head;

     while (self1->head && self2->head) {
          if (self1->head->data <= self2->head->data) {
               node->next = self1->head;
               self1->head = self1->head->next;
          } else {
               node->next = self2->head;
               self2->head = self2->head->next;
          }
          node = node->next;
     }

     self->size = self1->size + self2->size;
     SinglyLinkedList_Destroy(self1);
     SinglyLinkedList_Destroy(self2);
     
     return self;
}
