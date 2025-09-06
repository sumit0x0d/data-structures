#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <xor-linked-list.h>

typedef XorLinkedListNode Node;

struct xor_linked_list_node {
     DS_Data data;
     DS_Size xor;
};

struct xor_linked_list {
     Node *head;
     Node *tail;
     DS_Size data_size;
     DS_Size size;
};

static Node *_XorLinkedListNode_Create(const DS_Data data, DS_Size size);
static void _XorLinkedListNode_Destroy(Node *node);

XorLinkedList *XorLinkedList_Create(DS_Size size)
{
     XorLinkedList *xlList = (XorLinkedList *)malloc(sizeof (XorLinkedList));
     assert(xor_linked_list);
     xlList->head = NULL;
     xlList->tail = NULL;
     xlList->data_size = size;
     xlList->size = 0;
     return xlList;
}

void XorLinkedList_Destroy(XorLinkedList *xlList)
{
     _XorLinkedListNode_Destroy(xlList->head);
     free(xlList);
}

void XorLinkedList_PushHead(XorLinkedList *xlList, const DS_Data data)
{
     Node *node = _XorLinkedListNode_Create(data, xlList->data_size);
     node->xor = 0 ^ (DS_Size)xlList->head;
     xlList->head = node;
     if (!xlList->size) {
          xlList->tail = node;
     }
     xlList->size++;
}

void XorLinkedList_PushTail(XorLinkedList *xlList, const DS_Data data)
{
     Node *node = _XorLinkedListNode_Create(data, xlList->data_size);
     node->xor = (DS_Size)xlList->tail ^ 0;
     xlList->tail = node;
     if (!xlList->size) {
          xlList->head = node;
     }
     xlList->size++;
}

static Node *_XorLinkedListNode_Create(const DS_Data data, DS_Size size)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);  
     node->data = malloc(size);
     assert(node);
     memcpy(node->data, data, size);
     return node;
}

static void _XorLinkedListNode_Destroy(Node *node)
{
     free(node->data);
     free(node);
}
