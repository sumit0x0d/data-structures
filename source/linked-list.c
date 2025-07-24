#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <linked-list.h>

typedef LinkedListNode Node;
typedef LinkedListTraverse Traverse;

struct linked_list_node {
     void *data;
     Node *next;
};

struct linked_list {
     Node *head;
     Node *tail;
     size_t data_size;
     size_t size;
};

static Node *_LinkedListNode_Create(const void *data, size_t dSize);
static void _LinkedListNode_Destroy(LinkedListNode *node);

LinkedList *LinkedList_Create(size_t dSize)
{
     LinkedList *lList = (LinkedList *)malloc(sizeof (LinkedList));
     assert(lList);
     lList->head = NULL;
     lList->tail = NULL;
     lList->data_size = dSize;
     lList->size = 0;
     return lList;
}

void LinkedList_Destroy(LinkedList *lList)
{
     free(lList->head);
     free(lList);
}

void LinkedList_PushHead(LinkedList *lList, const void *data)
{
     Node *node = _LinkedListNode_Create(data, lList->data_size);
     if (lList->size) {
          node->next = lList->head;
     } else {
          node->next = NULL;
          lList->tail = node;
     }
     lList->head = node;
     lList->size++;
}

void LinkedList_PushTail(LinkedList *lList, const void *data)
{
     Node *node = _LinkedListNode_Create(data, lList->data_size);
     node->next = NULL;
     if (lList->size) {
          lList->tail->next = node;
     } else {
          lList->head = node;
     }
     lList->tail = node;
     lList->size++;
}

void LinkedList_PopHead(LinkedList *lList)
{
     Node *node = lList->head;
     lList->head = lList->head->next;
     if (!lList->head) {
          lList->tail = NULL;
     }
     _LinkedListNode_Destroy(node);
     lList->size--;
}

void LinkedList_PopTail(LinkedList *lList)
{
     if (lList->head == lList->tail) {
          free(lList->head);
          lList->head = NULL;
          lList->tail = NULL;
          return;
     }
     Node *node = lList->head;
     while (node->next != lList->tail) {
          node = node->next;
     }
     node->next = NULL;
     free(lList->tail);
     lList->tail = node;
     lList->size--;
}

void LinkedList_Traverse(LinkedList *lList, Traverse traverse, void *uData)
{
     Node *node = lList->head;
     while (node) {
          traverse(node->data, uData);
          node = node->next;
     }
}

void *LinkedListNode_GetData(LinkedListNode *node)
{
     return node->data;
}

void LinkedList_SetData(LinkedList *lList, LinkedListNode *node, const void *data)
{
     memcpy(node->data, data, lList->size);
}

LinkedListNode *LinkedList_DetectCycle(LinkedList *lList)
{
     Node* tortoise = lList->head;
     Node* hare = lList->head;
     while (hare && hare->next) {
          if (tortoise == hare) {
               return tortoise;
          }
          tortoise = tortoise->next;
          hare = hare->next->next;
     }
     return NULL;
}

LinkedListNode *LinkedList_GetMiddleNode(LinkedList *lList)
{
     Node* tortoise = lList->head;
     Node* hare = lList->head;
     while (hare && hare->next) {
          tortoise = tortoise->next;
          hare = hare->next->next;
     }
     return tortoise;
}

LinkedList *LinkedList_MergeSorted(LinkedList *lList1, LinkedList *lList2)
{
     LinkedList *lList = LinkedList_Create(lList1->data_size);
     if (lList1->head->data <= lList2->head->data) {
          lList->head = lList1->head;
          lList1->head = lList1->head->next;
     } else {
          lList->head = lList2->head;
          lList2->head = lList2->head->next;
     }
     if (lList1->tail->data <= lList2->tail->data) {
          lList->tail = lList2->tail;
     } else {
          lList->tail = lList1->tail;
     }
     Node *node = lList->head;
     while (lList1->head && lList2->head) {
          if (lList1->head->data <= lList2->head->data) {
               node->next = lList1->head;
               lList1->head = lList1->head->next;
          } else {
               node->next = lList2->head;
               lList2->head = lList2->head->next;
          }
          node = node->next;
     }
     lList->size = lList1->size + lList2->size;
     LinkedList_Destroy(lList1);
     LinkedList_Destroy(lList2);
     return lList;
}

static LinkedListNode *_LinkedListNode_Create(const void *data, size_t dSize)
{
     Node *node = (LinkedListNode *)malloc(sizeof (LinkedListNode));
     assert(node);
     node->data = malloc(dSize);
     assert(node);
     memcpy(node->data, data, dSize);
     return node;
}

static void _LinkedListNode_Destroy(LinkedListNode *node)
{
     free(node->data);
     free(node);
}
