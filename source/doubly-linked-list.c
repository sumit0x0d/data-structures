#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>

#include "doubly-linked-list-node.h"

struct DoublyLinkedList {
     DoublyLinkedListNode head;
     DoublyLinkedListNode tail;
     DS_Size              data_size;
     DS_Size              size;
};

DoublyLinkedList DoublyLinkedList_Create(
     DS_Size data_size
) {
     DoublyLinkedList doubly_linked_list;

     doubly_linked_list = (DoublyLinkedList)malloc(sizeof (struct DoublyLinkedList));
     if (!doubly_linked_list) {
          return NULL;
     }

     doubly_linked_list->head = NULL;
     doubly_linked_list->tail = NULL;
     doubly_linked_list->data_size = data_size;
     doubly_linked_list->size = 0;
     
     return doubly_linked_list;
}

DS_Void DoublyLinkedList_Destroy(
     DoublyLinkedList doubly_linked_list
) {
     DoublyLinkedListNode node;
     
     node = doubly_linked_list->head;
     while (node) {
          DoublyLinkedListNode next = node->next;
          DoublyLinkedListNode_Destroy(node);
          node = next;
     }
     
     free(doubly_linked_list);
}

DS_Size DoublyLinkedList_GetSize(
     DoublyLinkedList doubly_linked_list
) {
     return doubly_linked_list->size;
}

DS_Size DoublyLinkedList_GetDataSize(
     DoublyLinkedList doubly_linked_list
) {
     return doubly_linked_list->data_size;
}

DoublyLinkedListNode DoublyLinkedList_GetHead(
     DoublyLinkedList doubly_linked_list
) {
     return doubly_linked_list->head;
}

DoublyLinkedListNode DoublyLinkedList_GetTail(
     DoublyLinkedList doubly_linked_list
) {
     return doubly_linked_list->tail;
}

DS_Generic DoublyLinkedList_GetNodeData(
     DoublyLinkedListNode node
) {
     return node->data;
}

DS_Void DoublyLinkedList_SetNodeData(
     DoublyLinkedList     doubly_linked_list,
     DoublyLinkedListNode node,
     const DS_Generic     data
) {
     memcpy(node->data, data, doubly_linked_list->data_size);
}

DS_Void DoublyLinkedList_PushHead(
     DoublyLinkedList doubly_linked_list,
     const DS_Generic data
) {
     DoublyLinkedListNode node;
     
     node = DoublyLinkedListNode_Create(data, doubly_linked_list->data_size);
     node->previous = NULL;
     if (doubly_linked_list->size) {
          doubly_linked_list->head->previous = node;
          node->next = doubly_linked_list->head;
     } else {
          doubly_linked_list->tail = node;
          node->next = NULL;
     }
     doubly_linked_list->head = node;
     doubly_linked_list->size++;
}

DS_Void DoublyLinkedList_PushTail(
     DoublyLinkedList doubly_linked_list,
     const DS_Generic data
) {
     DoublyLinkedListNode node;
     
     node = DoublyLinkedListNode_Create(data, doubly_linked_list->data_size);
     node->next = NULL;
     
     if (doubly_linked_list->size) {
          doubly_linked_list->tail->next = node;
          node->previous = doubly_linked_list->tail;
     } else {
          doubly_linked_list->head = node;
          node->previous = NULL;
     }
     
     doubly_linked_list->tail = node;
     doubly_linked_list->size++;
}

DS_Void DoublyLinkedList_PopHead(
     DoublyLinkedList doubly_linked_list
) {
     DoublyLinkedListNode node;

     node = doubly_linked_list->head;
     
     doubly_linked_list->head = doubly_linked_list->head->next;
     if (!doubly_linked_list->head) {
          doubly_linked_list->tail = NULL;
     }
     
     DoublyLinkedListNode_Destroy(node);
     doubly_linked_list->size--;
}

DS_Void DoublyLinkedList_PopTail(
     DoublyLinkedList doubly_linked_list
) {
     DoublyLinkedListNode node;
     
     node = doubly_linked_list->tail;
     
     doubly_linked_list->tail = doubly_linked_list->tail->previous;
     if (doubly_linked_list->tail) {
          doubly_linked_list->tail->next = NULL;
     }
     
     DoublyLinkedListNode_Destroy(node);
     doubly_linked_list->size--;
}

DS_Void DoublyLinkedList_Remove(
     DoublyLinkedList     doubly_linked_list,
     DoublyLinkedListNode node
) {
     if (node->previous && node->previous->next == (DoublyLinkedListNode)node) {
          node->previous->next = node->next;
     } else {
          doubly_linked_list->head = doubly_linked_list->head->next;
     }
     
     if (node->next && node->next->previous == node) {
          node->next->previous = node->previous;
     } else {
          doubly_linked_list->tail = doubly_linked_list->tail->previous;
     }
     
     DoublyLinkedListNode_Destroy(node);
     doubly_linked_list->size--;
}

DS_Void DoublyLinkedList_Traverse(
     DoublyLinkedList doubly_linked_list,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
) {
     DoublyLinkedListNode node;
     
     node = doubly_linked_list->head;
     while (node) {
          unary_callback(node->data, unary_context);
          node = node->next;
     }
}
