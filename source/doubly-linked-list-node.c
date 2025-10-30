#include <stdlib.h>
#include <string.h>

#include "doubly-linked-list-node.h"

DoublyLinkedListNode DoublyLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     DoublyLinkedListNode this;

     this = (DoublyLinkedListNode)malloc(sizeof (struct DoublyLinkedListNode));
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

DS_Void DoublyLinkedListNode_Destroy(DoublyLinkedListNode this)
{
     free(this->data);
     free(this);
}
