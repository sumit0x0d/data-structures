#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "xor-linked-list-node.h"

struct XorLinkedList {
     XorLinkedListNode head;
     XorLinkedListNode tail;
     DS_Size           data_size;
     DS_Size           size;
};

XorLinkedList XorLinkedList_Create(
     DS_Size size
) {
     XorLinkedList xor_linked_list;
     
     xor_linked_list = (XorLinkedList)malloc(sizeof (struct XorLinkedList));
     if (!xor_linked_list) {
          return NULL;
     }
     
     xor_linked_list->head = NULL;
     xor_linked_list->tail = NULL;
     xor_linked_list->data_size = size;
     xor_linked_list->size = 0;
     
     return xor_linked_list;
}

DS_Void XorLinkedList_Destroy(
     XorLinkedList xor_linked_list
) {
     XorLinkedListNode_Destroy(xor_linked_list->head);
     free(xor_linked_list);
}

DS_Void XorLinkedList_PushHead(
     XorLinkedList    xor_linked_list,
     const DS_Generic data
) {
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, xor_linked_list->data_size);
     node->xor = 0 ^ (DS_Size)xor_linked_list->head;
     xor_linked_list->head = node;
     
     if (!xor_linked_list->size) {
          xor_linked_list->tail = node;
     }
     
     xor_linked_list->size++;
}

DS_Void XorLinkedList_PushTail(
     XorLinkedList    xor_linked_list,
     const DS_Generic data
) {
     XorLinkedListNode node;
     
     node = XorLinkedListNode_Create(data, xor_linked_list->data_size);
     node->xor = (DS_Size)xor_linked_list->tail ^ 0;
     xor_linked_list->tail = node;
     
     if (!xor_linked_list->size) {
          xor_linked_list->head = node;
     }
     
     xor_linked_list->size++;
}