#include <binary-heap.h>

struct BinaryHeapNode {
     void *data;
     BinaryHeapNode next;
};

struct BinaryHeap {
     BinaryHeapNode head;
     BinaryHeapNode tail;
     size_t data_size;
     size_t size;
     DS_CompareCallback compare_callback;
};