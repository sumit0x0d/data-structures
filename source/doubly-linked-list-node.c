#include <stdlib.h>
#include <string.h>

#include "doubly-linked-list-node.h"

DoublyLinkedListNode DoublyLinkedListNode_Create(
     const DS_Generic data,
     DS_Size          data_size
) {
     DoublyLinkedListNode node =
          (DoublyLinkedListNode)malloc(sizeof (struct DoublyLinkedListNode));
     if (!node) {
          return NULL;
     }
     node->data = malloc(data_size);
     if (!node->data) {
          free(node);
          return NULL;
     }
     memcpy(node->data, data, data_size);
     return node;
}

DS_Void DoublyLinkedListNode_Destroy(
     DoublyLinkedListNode node
) {
     free(node->data);
     free(node);
}
