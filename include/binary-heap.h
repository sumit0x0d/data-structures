#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <data-structures.h>

typedef struct BinaryHeap * BinaryHeap;
typedef struct BinaryHeapNode * BinaryHeapNode;

DATA_STRUCTURES_API
BinaryHeap BinaryHeap_Create(
     DS_Size data_size,
     DS_CallbackCompare compare_callback,
     DS_Generic compare_context
);

DATA_STRUCTURES_API
DS_Void BinaryHeap_Destroy(
     BinaryHeap heap
);

DATA_STRUCTURES_API
DS_Void BinaryHeap_Traverse(
     BinaryHeap binary_heap,
     DS_CallbackUnary unary_callback, 
     DS_Generic unary_context
);

#endif
