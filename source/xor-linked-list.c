#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "xor-linked-list/node.h"

struct XorLinkedList {
     XorLinkedListNode head;
     XorLinkedListNode tail;
     DS_Size data_size;
     DS_Size size;
};

XorLinkedList XorLinkedList_Create(DS_Size size)
{
     XorLinkedList this;
     
     this = (XorLinkedList)malloc(sizeof (struct XorLinkedList));
     if (!this) {
          return NULL;
     }
     
     this->head = NULL;
     this->tail = NULL;
     this->data_size = size;
     this->size = 0;
     
     return this;
}

DS_Void XorLinkedList_Destroy(XorLinkedList this)
{
     XorLinkedListNode_Destroy(this->head);
     free(this);
}

DS_Void XorLinkedList_PushHead(XorLinkedList this, const DS_Generic data)
{
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, this->data_size);
     node->xor = 0 ^ (DS_Size)this->head;
     this->head = node;
     
     if (!this->size) {
          this->tail = node;
     }
     
     this->size++;
}

DS_Void XorLinkedList_PushTail(XorLinkedList this, const DS_Generic data)
{
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, this->data_size);
     node->xor = (DS_Size)this->tail ^ 0;
     this->tail = node;
     
     if (!this->size) {
          this->head = node;
     }
     
     this->size++;
}