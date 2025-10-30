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
     DoublyLinkedList this;

     this = (DoublyLinkedList)malloc(sizeof (struct DoublyLinkedList));
     if (!this) {
          return NULL;
     }

     this->head = NULL;
     this->tail = NULL;
     this->data_size = data_size;
     this->size = 0;
     
     return this;
}

DS_Void DoublyLinkedList_Destroy(DoublyLinkedList this)
{
     DoublyLinkedListNode node;
     
     node = this->head;
     while (node) {
          DoublyLinkedListNode next = node->next;
          DoublyLinkedListNode_Destroy(node);
          node = next;
     }
     
     free(this);
}

DS_Size DoublyLinkedList_GetSize(DoublyLinkedList this)
{
     return this->size;
}

DS_Size DoublyLinkedList_GetDataSize(DoublyLinkedList this)
{
     return this->data_size;
}

DoublyLinkedListNode DoublyLinkedList_GetHead(DoublyLinkedList this)
{
     return this->head;
}

DoublyLinkedListNode DoublyLinkedList_GetTail(DoublyLinkedList this)
{
     return this->tail;
}

DS_Generic DoublyLinkedList_GetNodeData(DoublyLinkedListNode node)
{
     return node->data;
}

DS_Void DoublyLinkedList_SetNodeData(DoublyLinkedList this, DoublyLinkedListNode node, const DS_Generic data)
{
     memcpy(node->data, data, this->data_size);
}

DS_Void DoublyLinkedList_PushHead(DoublyLinkedList this, const DS_Generic data)
{
     DoublyLinkedListNode node;
     
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

DS_Void DoublyLinkedList_PushTail(DoublyLinkedList this, const DS_Generic data)
{
     DoublyLinkedListNode node;
     
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

DS_Void DoublyLinkedList_PopHead(DoublyLinkedList this)
{
     DoublyLinkedListNode node;

     node = this->head;
     
     this->head = this->head->next;
     if (!this->head) {
          this->tail = NULL;
     }
     
     DoublyLinkedListNode_Destroy(node);
     this->size--;
}

DS_Void DoublyLinkedList_PopTail(DoublyLinkedList this)
{
     DoublyLinkedListNode node;

     node = this->tail;

     this->tail = this->tail->previous;
     if (this->tail) {
          this->tail->next = NULL;
     }

     DoublyLinkedListNode_Destroy(node);
     this->size--;
}

DS_Void DoublyLinkedList_Remove(DoublyLinkedList this, DoublyLinkedListNode node)
{
     if (node->previous && node->previous->next == (DoublyLinkedListNode)node) {
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

DS_Void DoublyLinkedList_Traverse(DoublyLinkedList this, DS_UnaryCallback unary_callback)
{
     DoublyLinkedListNode node;

     node = this->head;
     while (node) {
          unary_callback.function(node->data, unary_callback.user_data);
          node = node->next;
     }
}
