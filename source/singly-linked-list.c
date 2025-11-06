#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <singly-linked-list.h>

#include "singly-linked-list/node.h"

struct SinglyLinkedList {
     SinglyLinkedListNode *head;
     SinglyLinkedListNode *tail;
     size_t data_size;
     size_t size;
};

SinglyLinkedList *SinglyLinkedList_Create(size_t data_size)
{
     SinglyLinkedList *this;

     this = (SinglyLinkedList *)malloc(sizeof (SinglyLinkedList));
     if (!this) {
          return NULL;
     }
     
     this->head = NULL;
     this->tail = NULL;
     this->data_size = data_size;
     this->size = 0;
     
     return this;
}

void SinglyLinkedList_Destroy(SinglyLinkedList *this)
{
     free(this->head);
     free(this);
}

void SinglyLinkedList_PushHead(SinglyLinkedList *this, const void *data)
{
     SinglyLinkedListNode *node;
     
     node = SinglyLinkedListNode_Create(data, this->data_size);
     
     if (this->size) {
          node->next = this->head;
     } else {
          node->next = NULL;
          this->tail = node;
     }
     
     this->head = node;
     this->size++;
}

void SinglyLinkedList_PushTail(SinglyLinkedList *this, const void *data)
{
     SinglyLinkedListNode *node;

     node = SinglyLinkedListNode_Create(data, this->data_size);
     node->next = NULL;

     if (this->size) {
          this->tail->next = node;
     } else {
          this->head = node;
     }

     this->tail = node;
     this->size++;
}

void SinglyLinkedList_PopHead(SinglyLinkedList *this)
{
     SinglyLinkedListNode *node;

     node = this->head;
     
     this->head = this->head->next;
     if (!this->head) {
          this->tail = NULL;
     }
     
     SinglyLinkedListNode_Destroy(node);
     this->size--;
}

void SinglyLinkedList_PopTail(SinglyLinkedList *this)
{
     SinglyLinkedListNode *node;
     
     if (this->size == 0) {
          return;
     }
     
     if (this->head == this->tail) {
          free(this->head);
          this->head = NULL;
          this->tail = NULL;
          return;
     }
     
     node = this->head;
     
     while (node->next != this->tail) {
          node = node->next;
     }
     
     node->next = NULL;
     free(this->tail);
     this->tail = node;
     this->size--;
}

void SinglyLinkedList_Traverse(SinglyLinkedList *this, SinglyLinkedListUnaryCallback unary_callback)
{
     SinglyLinkedListNode *node;

     node = this->head;
     while (node) {
          unary_callback.function(node->data, unary_callback.user_data);
          node = node->next;
     }
}

void *SinglyLinkedListNode_GetData(SinglyLinkedListNode *node)
{
     return node->data;
}

void SinglyLinkedList_SetData(SinglyLinkedList *this, SinglyLinkedListNode *node, const void *data)
{
     memcpy(node->data, data, this->data_size);
}

SinglyLinkedListNode *SinglyLinkedList_DetectCycle(SinglyLinkedList *this)
{
     SinglyLinkedListNode *tortoise;
     SinglyLinkedListNode *hare;

     tortoise = this->head;
     
     hare = this->head;
     while (hare && hare->next) {
          if (tortoise == hare) {
               return tortoise;
          }
          tortoise = tortoise->next;
          hare = hare->next->next;
     }
     
     return NULL;
}

SinglyLinkedListNode *SinglyLinkedList_GetMiddleNode(SinglyLinkedList *this)
{
     SinglyLinkedListNode *tortoise;
     SinglyLinkedListNode *hare;

     tortoise = this->head;
     
     hare = this->head;
     while (hare && hare->next) {
          tortoise = tortoise->next;
          hare = hare->next->next;
     }

     return tortoise;
}

SinglyLinkedList *SinglyLinkedList_MergeSorted(SinglyLinkedList *singly_linked_list1, SinglyLinkedList *singly_linked_list2)
{
     SinglyLinkedList *this;
     SinglyLinkedListNode *node;

     this = SinglyLinkedList_Create(singly_linked_list1->data_size);

     if (singly_linked_list1->head->data <= singly_linked_list2->head->data) {
          this->head = singly_linked_list1->head;
          singly_linked_list1->head = singly_linked_list1->head->next;
     } else {
          this->head = singly_linked_list2->head;
          singly_linked_list2->head = singly_linked_list2->head->next;
     }

     if (singly_linked_list1->tail->data <= singly_linked_list2->tail->data) {
          this->tail = singly_linked_list2->tail;
     } else {
          this->tail = singly_linked_list1->tail;
     }

     node = this->head;

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

     this->size = singly_linked_list1->size + singly_linked_list2->size;
     SinglyLinkedList_Destroy(singly_linked_list1);
     SinglyLinkedList_Destroy(singly_linked_list2);
     
     return this;
}
