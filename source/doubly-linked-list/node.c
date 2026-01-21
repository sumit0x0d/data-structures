#include <stdlib.h>
#include <string.h>

#include "node.h"

DoublyLinkedListNode *DoublyLinkedListNode_Create(const void *data, size_t data_size)
{
   DoublyLinkedListNode *this;

   this = (DoublyLinkedListNode *)malloc(sizeof (DoublyLinkedListNode));
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

void DoublyLinkedListNode_Destroy(DoublyLinkedListNode *this)
{
   free(this->data);
   free(this);
}
