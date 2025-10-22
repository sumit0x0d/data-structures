#include <stdlib.h>
#include <string.h>

#include "singly-linked-list-node.h"

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     SinglyLinkedListNode self;
     
     self = (SinglyLinkedListNode)malloc(sizeof (struct SinglyLinkedListNode));
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

DS_Void SinglyLinkedListNode_Destroy(SinglyLinkedListNode self)
{
     free(self->data);
     free(self);
}
