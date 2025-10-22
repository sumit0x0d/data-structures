#include <binary-heap.h>

struct BinaryHeapNode {
     DS_Generic data;
     BinaryHeapNode next;
};

struct BinaryHeap {
     BinaryHeapNode head;
     BinaryHeapNode tail;
     DS_Size data_size;
     DS_Size size;
     DS_CompareCallback compare_callback;
};