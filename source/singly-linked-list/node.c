#include <stdlib.h>
#include <string.h>

#include "node.h"

SinglyLinkedListNode *SinglyLinkedListNode_Create(const void *data, size_t data_size)
{
     SinglyLinkedListNode *this;
     
     this = (SinglyLinkedListNode *)malloc(sizeof (SinglyLinkedListNode));
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

void SinglyLinkedListNode_Destroy(SinglyLinkedListNode *this)
{
     free(this->data);
     free(this);
}
