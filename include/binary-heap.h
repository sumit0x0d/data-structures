#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct binary_heap BinaryHeap;
typedef struct binary_heap_node BinaryHeapNode;
typedef int (*BinaryHeapCompare)(const void *data1, const void *data2, void *uData);
typedef void (*BinaryHeapTraverse)(void *data, void *uData);

struct binary_heap_node {
     void *data;
     struct binary_heap_node *next;
};

struct binary_heap {
     BinaryHeapNode *head;
     BinaryHeapNode *tail;
     size_t data_size;
     size_t size;
     BinaryHeapCompare compare;
     void *uData;
};

BinaryHeap *BinaryHeap_Create(size_t dSize, BinaryHeapCompare bhCompare, void *uData);
void BinaryHeap_Destroy(BinaryHeap *bHeap);

void BinaryHeap_Traverse(BinaryHeap *bHeap, BinaryHeapTraverse bhTraverse, void *uData);

#endif
