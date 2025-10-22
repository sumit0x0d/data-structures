#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "xor-linked-list-node.h"

struct XorLinkedList {
     XorLinkedListNode head;
     XorLinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

XorLinkedList XorLinkedList_Create(DS_Size size)
{
     XorLinkedList self;
     
     self = (XorLinkedList)malloc(sizeof (struct XorLinkedList));
     if (!self) {
          return NULL;
     }
     
     self->head = NULL;
     self->tail = NULL;
     self->data_size = size;
     self->size = 0;
     
     return self;
}

DS_Void XorLinkedList_Destroy(XorLinkedList self)
{
     XorLinkedListNode_Destroy(self->head);
     free(self);
}

DS_Void XorLinkedList_PushHead(XorLinkedList self, const DS_Generic data)
{
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, self->data_size);
     node->xor = 0 ^ (DS_Size)self->head;
     self->head = node;
     
     if (!self->size) {
          self->tail = node;
     }
     
     self->size++;
}

DS_Void XorLinkedList_PushTail(XorLinkedList self, const DS_Generic data)
{
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, self->data_size);
     node->xor = (DS_Size)self->tail ^ 0;
     self->tail = node;
     
     if (!self->size) {
          self->head = node;
     }
     
     self->size++;
}