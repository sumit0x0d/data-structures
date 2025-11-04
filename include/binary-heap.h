#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H



typedef struct BinaryHeap * BinaryHeap;
typedef struct BinaryHeapNode * BinaryHeapNode;

__attribute__((visibility("default")))
BinaryHeap BinaryHeap_Create(size_t data_size, DS_CompareCallback compare_callback);

__attribute__((visibility("default")))
void BinaryHeap_Destroy(BinaryHeap this);

__attribute__((visibility("default")))
void BinaryHeap_Traverse(BinaryHeap this, DS_UnaryCallback unary_callback);

#endif
