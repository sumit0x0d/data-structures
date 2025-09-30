#include <binary-heap.h>

struct binary_heap_node {
     DS_Generic data;
     struct binary_heap_node *next;
};

struct binary_heap {
     BinaryHeapNode head;
     BinaryHeapNode tail;
     DS_Size data_size;
     DS_Size size;
     DS_CallbackCompare compare_callback;
     DS_Generic compare_context;
};
