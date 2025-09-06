#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct binary_heap BinaryHeap;
typedef struct binary_heap_node BinaryHeapNode;

struct binary_heap_node {
     DS_Data data;
     struct binary_heap_node *next;
};

struct binary_heap {
     BinaryHeapNode *head;
     BinaryHeapNode *tail;
     DS_Size data_size;
     DS_Size size;
     BinaryHeapCompare compare;
     void *uData;
};

BinaryHeap *BinaryHeap_Create(DS_Size size, BinaryHeapCompare bhCompare, void *uData);
void BinaryHeap_Destroy(BinaryHeap *bHeap);

void BinaryHeap_Traverse(BinaryHeap *bHeap, BinaryHeapTraverse bhTraverse, void *uData);

#endif
