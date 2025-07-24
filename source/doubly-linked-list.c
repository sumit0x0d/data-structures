#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>

typedef DoublyLinkedListNode Node;
typedef DoublyLinkedListTraverse Traverse;

struct doubly_linked_list_node {
     void *data;
     Node *previous;
     Node *next;
};

struct doubly_linked_list {
     Node *head;
     Node *tail;
     size_t data_size;
     size_t size;
};

static Node *_DoublyLinkedListNode_Create(const void *data, size_t dSize);
static void _DoublyLinkedListNode_Destroy(Node *node);

DoublyLinkedList *DoublyLinkedList_Create(size_t dSize)
{
     DoublyLinkedList *dlList = (DoublyLinkedList *)malloc(sizeof (DoublyLinkedList));
     assert(doubly_linked_list);
     dlList->head = NULL;
     dlList->tail = NULL;
     dlList->data_size = dSize;
     dlList->size = 0;
     return dlList;
}

void DoublyLinkedList_Destroy(DoublyLinkedList *dlList)
{
     Node *node = dlList->head;
     while (node) {
          Node *nnode = node->next;
          _DoublyLinkedListNode_Destroy(node);
          node = nnode;
     }
     free(dlList);
}

size_t DoublyLinkedList_GetSize(DoublyLinkedList *dlList)
{
     return dlList->size;
}

size_t DoublyLinkedList_GetDataSize(DoublyLinkedList *dlList)
{
     return dlList->data_size;
}

DoublyLinkedListNode *DoublyLinkedList_GetHead(DoublyLinkedList *dlList)
{
     return dlList->head;
}

DoublyLinkedListNode *DoublyLinkedList_GetTail(DoublyLinkedList *dlList)
{
     return dlList->tail;
}

void *DoublyLinkedListNode_GetData(DoublyLinkedListNode *node)
{
     return node->data;
}

void DoublyLinkedList_set_data(DoublyLinkedList *dlList, DoublyLinkedListNode *node, const void *data)
{
     memcpy(node->data, data, dlList->data_size);
}

void DoublyLinkedList_PushHead(DoublyLinkedList *dlList, const void *data)
{
     Node *node = _DoublyLinkedListNode_Create(data, dlList->data_size);
     node->previous = NULL;
     if (dlList->size) {
          dlList->head->previous = node;
          node->next = dlList->head;
     } else {
          dlList->tail = node;
          node->next = NULL;
     }
     dlList->head = node;
     dlList->size++;
}

void DoublyLinkedList_PushTail(DoublyLinkedList *dlList, const void *data)
{
     Node *node = _DoublyLinkedListNode_Create(data, dlList->data_size);
     node->next = NULL;
     if (dlList->size) {
          dlList->tail->next = node;
          node->previous = dlList->tail;
     } else {
          dlList->head = node;
          node->previous = NULL;
     }
     dlList->tail = node;
     dlList->size++;
}

void DoublyLinkedList_PopHead(DoublyLinkedList *dlList)
{
     Node *node = dlList->head;
     dlList->head = dlList->head->next;
     if (!dlList->head) {
          dlList->tail = NULL;
     }
     _DoublyLinkedListNode_Destroy(node);
     dlList->size--;
}

void DoublyLinkedList_PopTail(DoublyLinkedList *dlList)
{
     Node *node = dlList->tail;
     dlList->tail = dlList->tail->previous;
     if (dlList->tail) {
          dlList->tail->next = NULL;
     }
     _DoublyLinkedListNode_Destroy(node);
     dlList->size--;
}

void DoublyLinkedList_Remove(DoublyLinkedList *dlList, Node *node)
{
     if (node->previous && node->previous->next == (Node *)node) {
          node->previous->next = node->next;
     } else {
          dlList->head = dlList->head->next;
     }
     if (node->next && node->next->previous == node) {
          node->next->previous = node->previous;
     } else {
          dlList->tail = dlList->tail->previous;
     }
     _DoublyLinkedListNode_Destroy(node);
     dlList->size--;
}

void DoublyLinkedList_Traverse(DoublyLinkedList *dlList, Traverse traverse, void *uData)
{
     Node *node = dlList->head;
     while (node) {
          traverse(node->data, uData);
          node = node->next;
     }
}

static Node *_DoublyLinkedListNode_Create(const void *data, size_t dSize)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);
     node->data = malloc(dSize);
     assert(node->data);
     memcpy(node->data, data, dSize);
     return node;
}

static void _DoublyLinkedListNode_Destroy(Node *node)
{
     free(node->data);
     free(node);
}
