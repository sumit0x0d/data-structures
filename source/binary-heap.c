#include <binary-heap.h>

struct binary_heap_node {
     DS_Data data;
     struct binary_heap_node *next;
};

struct binary_heap {
     BinaryHeapNode *head;
     BinaryHeapNode *tail;
     DS_Size data_size;
     DS_Size size;
     DS_FunctionCompare compare_function;
     DS_Context compare_context;
};
