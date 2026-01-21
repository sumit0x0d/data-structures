#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>

#include "doubly-linked-list/node.h"

struct DoublyLinkedList {
   DoublyLinkedListNode *head;
   DoublyLinkedListNode *tail;
   size_t data_size;
   size_t size;
};

DoublyLinkedList *DoublyLinkedList_Create(size_t data_size)
{
   DoublyLinkedList *this;

   this = (DoublyLinkedList *)malloc(sizeof (DoublyLinkedList));
   if (!this) {
      return NULL;
   }

   this->head = NULL;
   this->tail = NULL;
   this->data_size = data_size;
   this->size = 0;

   return this;
}

void DoublyLinkedList_Destroy(DoublyLinkedList *this)
{
   DoublyLinkedListNode *node;

   node = this->head;
   while (node) {
      DoublyLinkedListNode *next = node->next;
      DoublyLinkedListNode_Destroy(node);
      node = next;
   }

   free(this);
}

size_t DoublyLinkedList_GetSize(DoublyLinkedList *this)
{
   return this->size;
}

size_t DoublyLinkedList_GetDataSize(DoublyLinkedList *this)
{
   return this->data_size;
}

DoublyLinkedListNode *DoublyLinkedList_GetHead(DoublyLinkedList *this)
{
   return this->head;
}

DoublyLinkedListNode *DoublyLinkedList_GetTail(DoublyLinkedList *this)
{
   return this->tail;
}

void *DoublyLinkedList_GetNodeData(DoublyLinkedListNode *node)
{
   return node->data;
}

void DoublyLinkedList_SetNodeData(DoublyLinkedList *this,
   DoublyLinkedListNode *node, const void *data)
{
   memcpy(node->data, data, this->data_size);
}

void DoublyLinkedList_PushHead(DoublyLinkedList *this, const void *data)
{
   DoublyLinkedListNode *node;

   node = DoublyLinkedListNode_Create(data, this->data_size);
   node->previous = NULL;

   if (this->size) {
      this->head->previous = node;
      node->next = this->head;
   } else {
      this->tail = node;
      node->next = NULL;
   }

   this->head = node;
   this->size++;
}

void DoublyLinkedList_PushTail(DoublyLinkedList *this, const void *data)
{
   DoublyLinkedListNode *node;

   node = DoublyLinkedListNode_Create(data, this->data_size);
   node->next = NULL;

   if (this->size) {
      this->tail->next = node;
      node->previous = this->tail;
   } else {
      this->head = node;
      node->previous = NULL;
   }

   this->tail = node;
   this->size++;
}

void DoublyLinkedList_PopHead(DoublyLinkedList *this)
{
   DoublyLinkedListNode *node;

   node = this->head;

   this->head = this->head->next;
   if (!this->head) {
      this->tail = NULL;
   }

   DoublyLinkedListNode_Destroy(node);
   this->size--;
}

void DoublyLinkedList_PopTail(DoublyLinkedList *this)
{
   DoublyLinkedListNode *node;

   node = this->tail;

   this->tail = this->tail->previous;
   if (this->tail) {
      this->tail->next = NULL;
   }

   DoublyLinkedListNode_Destroy(node);
   this->size--;
}

void DoublyLinkedList_RemoveNode(DoublyLinkedList *this, DoublyLinkedListNode *node)
{
   if (node->previous && node->previous->next == (DoublyLinkedListNode *)node) {
      node->previous->next = node->next;
   } else {
      this->head = this->head->next;
   }

   if (node->next && node->next->previous == node) {
      node->next->previous = node->previous;
   } else {
      this->tail = this->tail->previous;
   }

   DoublyLinkedListNode_Destroy(node);
   this->size--;
}

void DoublyLinkedList_Traverse(DoublyLinkedList *this,
   DoublyLinkedListUnaryCallback unary_callback)
{
   DoublyLinkedListNode *node;

   node = this->head;
   while (node) {
      unary_callback.function(node->data, unary_callback.user_data);
      node = node->next;
   }
}
