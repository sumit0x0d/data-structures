#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <xor-linked-list.h>

typedef XorLinkedListNode Node;

struct xor_linked_list_node {
     void *data;
     size_t xor;
};

struct xor_linked_list {
     Node *head;
     Node *tail;
     size_t data_size;
     size_t size;
};

static Node *_XorLinkedListNode_Create(const void *data, size_t dSize);
static void _XorLinkedListNode_Destroy(Node *node);

XorLinkedList *XorLinkedList_Create(size_t dSize)
{
     XorLinkedList *xlList = (XorLinkedList *)malloc(sizeof (XorLinkedList));
     assert(xor_linked_list);
     xlList->head = NULL;
     xlList->tail = NULL;
     xlList->data_size = dSize;
     xlList->size = 0;
     return xlList;
}

void XorLinkedList_Destroy(XorLinkedList *xlList)
{
     _XorLinkedListNode_Destroy(xlList->head);
     free(xlList);
}

void XorLinkedList_PushHead(XorLinkedList *xlList, const void *data)
{
     Node *node = _XorLinkedListNode_Create(data, xlList->data_size);
     node->xor = 0 ^ (size_t)xlList->head;
     xlList->head = node;
     if (!xlList->size) {
          xlList->tail = node;
     }
     xlList->size++;
}

void XorLinkedList_PushTail(XorLinkedList *xlList, const void *data)
{
     Node *node = _XorLinkedListNode_Create(data, xlList->data_size);
     node->xor = (size_t)xlList->tail ^ 0;
     xlList->tail = node;
     if (!xlList->size) {
          xlList->head = node;
     }
     xlList->size++;
}

static Node *_XorLinkedListNode_Create(const void *data, size_t dSize)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);  
     node->data = malloc(dSize);
     assert(node);
     memcpy(node->data, data, dSize);
     return node;
}

static void _XorLinkedListNode_Destroy(Node *node)
{
     free(node->data);
     free(node);
}
