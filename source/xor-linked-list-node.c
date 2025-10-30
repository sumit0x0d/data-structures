#include <stdlib.h>
#include <string.h>

#include "xor-linked-list-node.h"

XorLinkedListNode XorLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     XorLinkedListNode this;
     
     this = (XorLinkedListNode)malloc(sizeof (struct XorLinkedListNode));
     if (!this) {
          return NULL;
     }  
     
     this->data = malloc(data_size);
     if(!this->data) {
          free(this);
          return NULL;
     }
     
     memcpy(this->data, data, data_size);
     return this;
}

DS_Void XorLinkedListNode_Destroy(XorLinkedListNode this)
{
     free(this->data);
     free(this);
}
