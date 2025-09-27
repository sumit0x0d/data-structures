#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <data-structures.h>

typedef struct binary_heap * BinaryHeap;
typedef struct binary_heap_node * BinaryHeapNode;

DS_API
BinaryHeap BinaryHeap_Create(DS_Size data_size, DS_FunctionCompare compare_function, DS_Context compare_context);

DS_API
DS_Void BinaryHeap_Destroy(BinaryHeap heap);

DS_API
DS_Void BinaryHeap_Traverse(BinaryHeap heap, DS_FunctionUnary unary_function, DS_Context unary_context);

#endif
