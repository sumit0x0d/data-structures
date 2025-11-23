#ifndef DATA_STRUCTURES_BINARY_HEAP_H
#define DATA_STRUCTURES_BINARY_HEAP_H

#include <stddef.h>

typedef struct BinaryHeap BinaryHeap;
typedef struct BinaryHeapNode BinaryHeapNode;

typedef enum {
     BINARY_HEAP_COMPARE_LESS = -1,
     BINARY_HEAP_COMPARE_EQUAL = 0,
     BINARY_HEAP_COMPARE_GREATER = 1
} BinaryHeapCompare;

typedef struct {
     BinaryHeapCompare (*function)(const void *data1,
          const void *data2,
          void *user_data);
     void *user_data;
} BinaryHeapCompareCallback;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} BinaryHeapUnaryCallback;

__attribute__((visibility("default")))
BinaryHeap *BinaryHeap_Create(size_t data_size, BinaryHeapCompareCallback compare_callback);

__attribute__((visibility("default")))
void BinaryHeap_Destroy(BinaryHeap *this);

__attribute__((visibility("default")))
void BinaryHeap_Traverse(BinaryHeap *this, BinaryHeapUnaryCallback unary_callback);

#endif
