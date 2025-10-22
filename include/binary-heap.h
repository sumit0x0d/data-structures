#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <data-structures.h>

typedef struct BinaryHeap * BinaryHeap;
typedef struct BinaryHeapNode * BinaryHeapNode;

DATA_STRUCTURES_API
BinaryHeap BinaryHeap_Create(DS_Size data_size, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void BinaryHeap_Destroy(BinaryHeap self);

DATA_STRUCTURES_API
DS_Void BinaryHeap_Traverse(BinaryHeap self, DS_UnaryCallback unary_callback);

#endif
