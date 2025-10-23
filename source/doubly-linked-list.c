#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>

#include "doubly-linked-list-node.h"

struct DoublyLinkedList {
     DoublyLinkedListNode head;
     DoublyLinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

DoublyLinkedList DoublyLinkedList_Create(DS_Size data_size)
{
     DoublyLinkedList self;

     self = (DoublyLinkedList)malloc(sizeof (struct DoublyLinkedList));
     if (!self) {
          return NULL;
     }

     self->head = NULL;
     self->tail = NULL;
     self->data_size = data_size;
     self->size = 0;
     
     return self;
}

DS_Void DoublyLinkedList_Destroy(DoublyLinkedList self)
{
     DoublyLinkedListNode node;
     
     node = self->head;
     while (node) {
          DoublyLinkedListNode next = node->next;
          DoublyLinkedListNode_Destroy(node);
          node = next;
     }
     
     free(self);
}

DS_Size DoublyLinkedList_GetSize(DoublyLinkedList self)
{
     return self->size;
}

DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList self)
{
     return self->data_size;
}

DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList self)
{
     return self->head;
}

DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList self)
{
     return self->tail;
}

DS_Generic DoublyLinkedList_GetNodeData(DoublyLinkedListNode node)
{
     return node->data;
}

DS_Void DoublyLinkedList_SetNodeData(DoublyLinkedList self, DoublyLinkedListNode node, const DS_Generic data)
{
     memcpy(node->data, data, self->data_size);
}

DS_Void DoublyLinkedList_PushHead(DoublyLinkedList self, const DS_Generic data)
{
     DoublyLinkedListNode node;
     
     node = DoublyLinkedListNode_Create(data, self->data_size);
     node->previous = NULL;

     if (self->size) {
          self->head->previous = node;
          node->next = self->head;
     } else {
          self->tail = node;
          node->next = NULL;
     }

     self->head = node;
     self->size++;
}

DS_Void DoublyLinkedList_PushTail(DoublyLinkedList self, const DS_Generic data)
{
     DoublyLinkedListNode node;
     
     node = DoublyLinkedListNode_Create(data, self->data_size);
     node->next = NULL;
     
     if (self->size) {
          self->tail->next = node;
          node->previous = self->tail;
     } else {
          self->head = node;
          node->previous = NULL;
     }
     
     self->tail = node;
     self->size++;
}

DS_Void DoublyLinkedList_PopHead(DoublyLinkedList self)
{
     DoublyLinkedListNode node;

     node = self->head;
     
     self->head = self->head->next;
     if (!self->head) {
          self->tail = NULL;
     }
     
     DoublyLinkedListNode_Destroy(node);
     self->size--;
}

DS_Void DoublyLinkedList_PopTail(DoublyLinkedList self)
{
     DoublyLinkedListNode node;

     node = self->tail;

     self->tail = self->tail->previous;
     if (self->tail) {
          self->tail->next = NULL;
     }

     DoublyLinkedListNode_Destroy(node);
     self->size--;
}

DS_Void DoublyLinkedList_Remove(DoublyLinkedList self, DoublyLinkedListNode node)
{
     if (node->previous && node->previous->next == (DoublyLinkedListNode)node) {
          node->previous->next = node->next;
     } else {
          self->head = self->head->next;
     }

     if (node->next && node->next->previous == node) {
          node->next->previous = node->previous;
     } else {
          self->tail = self->tail->previous;
     }

     DoublyLinkedListNode_Destroy(node);
     self->size--;
}

DS_Void DoublyLinkedList_Traverse(DoublyLinkedList self, DS_UnaryCallback unary_callback)
{
     DoublyLinkedListNode node;

     node = self->head;
     while (node) {
          unary_callback.function(node->data, unary_callback.user_data);
          node = node->next;
     }
}
