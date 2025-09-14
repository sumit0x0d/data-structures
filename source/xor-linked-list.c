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
     Node head;
     Node tail;
     DS_Size data_size;
     DS_Size size;
};

static Node _XorLinkedListNode_Create(const DS_Data data, DS_Size size);
static void _XorLinkedListNode_Destroy(Node node);

XorLinkedList XorLinkedList_Create(DS_Size size)
{
     XorLinkedList list = (XorLinkedList )malloc(sizeof (XorLinkedList));
     if (!list) {
          return NULL;
     }
     list->head = NULL;
     list->tail = NULL;
     list->data_size = size;
     list->size = 0;
     return list;
}

void XorLinkedList_Destroy(XorLinkedList list)
{
     _XorLinkedListNode_Destroy(list->head);
     free(list);
}

void XorLinkedList_PushHead(XorLinkedList list, const DS_Data data)
{
     Node node = _XorLinkedListNode_Create(data, list->data_size);
     node->xor = 0 ^ (DS_Size)list->head;
     list->head = node;
     if (!list->size) {
          list->tail = node;
     }
     list->size++;
}

void XorLinkedList_PushTail(XorLinkedList list, const DS_Data data)
{
     Node node = _XorLinkedListNode_Create(data, list->data_size);
     node->xor = (DS_Size)list->tail ^ 0;
     list->tail = node;
     if (!list->size) {
          list->head = node;
     }
     list->size++;
}

static Node _XorLinkedListNode_Create(const DS_Data data, DS_Size size)
{
     Node node = (Node )malloc(sizeof (Node));
     assert(node);  
     node->data = malloc(size);
     assert(node);
     memcpy(node->data, data, size);
     return node;
}

static void _XorLinkedListNode_Destroy(Node node)
{
     free(node->data);
     free(node);
}
