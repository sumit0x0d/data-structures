#include <binary-heap.h>

struct BinaryHeapNode {
    DS_Generic data;
    struct BinaryHeapNode *next;
};

struct BinaryHeap {
    BinaryHeapNode head;
    BinaryHeapNode tail;
    DS_Size data_size;
    DS_Size size;
    DS_CallbackCompare compare_callback;
    DS_Generic compare_context;
};