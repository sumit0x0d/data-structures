#include <stdlib.h>
#include <string.h>

#include "xor-linked-list-node.h"

XorLinkedListNode XorLinkedListNode_Create(const DS_Generic data, DS_Size data_size)
{
     XorLinkedListNode node =
          (XorLinkedListNode)malloc(sizeof (struct XorLinkedListNode));
     if (!node) {
          return NULL;
     }  
     node->data = malloc(data_size);
     if(!node->data) {
          free(node);
          return NULL;
     }
     memcpy(node->data, data, data_size);
     return node;
}

DS_Void XorLinkedListNode_Destroy(XorLinkedListNode node)
{
     free(node->data);
     free(node);
}
