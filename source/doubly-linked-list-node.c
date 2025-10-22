#include <stdlib.h>
#include <string.h>

#include "doubly-linked-list-node.h"

DoublyLinkedListNode DoublyLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     DoublyLinkedListNode self;

     self = (DoublyLinkedListNode)malloc(sizeof (struct DoublyLinkedListNode));
     if (!self) {
          return NULL;
     }

     self->data = malloc(data_size);
     if (!self->data) {
          free(self);
          return NULL;
     }

     memcpy(self->data, data, data_size);
     
     return self;
}

DS_Void DoublyLinkedListNode_Destroy(DoublyLinkedListNode self)
{
     free(self->data);
     free(self);
}
