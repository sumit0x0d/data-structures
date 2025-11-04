#include <stdlib.h>
#include <string.h>

#include "node.h"

SinglyLinkedListNode SinglyLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     SinglyLinkedListNode this;
     
     this = (SinglyLinkedListNode)malloc(sizeof (struct SinglyLinkedListNode));
     if (!this) {
          return NULL;
     }
     
     this->data = malloc(data_size);
     if (!this->data) {
          free(this);
          return NULL;
     }
     
     memcpy(this->data, data, data_size);
     
     return this;
}

DS_Void SinglyLinkedListNode_Destroy(SinglyLinkedListNode this)
{
     free(this->data);
     free(this);
}
