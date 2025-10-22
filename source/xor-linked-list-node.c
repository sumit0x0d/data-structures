#include <stdlib.h>
#include <string.h>

#include "xor-linked-list-node.h"

XorLinkedListNode XorLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     XorLinkedListNode self;
     
     self = (XorLinkedListNode)malloc(sizeof (struct XorLinkedListNode));
     if (!self) {
          return NULL;
     }  
     
     self->data = malloc(data_size);
     if(!self->data) {
          free(self);
          return NULL;
     }
     
     memcpy(self->data, data, data_size);
     return self;
}

DS_Void XorLinkedListNode_Destroy(XorLinkedListNode self)
{
     free(self->data);
     free(self);
}
