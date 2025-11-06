#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "xor-linked-list/node.h"

struct XorLinkedList {
     XorLinkedListNode *head;
     XorLinkedListNode *tail;
     size_t data_size;
     size_t size;
};

XorLinkedList *XorLinkedList_Create(size_t size)
{
     XorLinkedList *this;
     
     this = (XorLinkedList *)malloc(sizeof (XorLinkedList));
     if (!this) {
          return NULL;
     }
     
     this->head = NULL;
     this->tail = NULL;
     this->data_size = size;
     this->size = 0;
     
     return this;
}

void XorLinkedList_Destroy(XorLinkedList *this)
{
     XorLinkedListNode_Destroy(this->head);
     free(this);
}

void XorLinkedList_PushHead(XorLinkedList *this, const void *data)
{
     XorLinkedListNode *node;
     
     node = XorLinkedListNode_Create(data, this->data_size);
     node->xor = 0 ^ (size_t)this->head;
     this->head = node;
     
     if (!this->size) {
          this->tail = node;
     }
     
     this->size++;
}

void XorLinkedList_PushTail(XorLinkedList *this, const void *data)
{
     XorLinkedListNode *node;
     
     node = XorLinkedListNode_Create(data, this->data_size);
     node->xor = (size_t)this->tail ^ 0;
     this->tail = node;
     
     if (!this->size) {
          this->head = node;
     }
     
     this->size++;
}