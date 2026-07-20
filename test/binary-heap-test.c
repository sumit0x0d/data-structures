#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <binary-heap.h>

static int _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   BinaryHeap *binary_heap;
   int i, value;
   BinaryHeapCompareCallback compare_callback;
   BinaryHeapUnaryCallback unary_callback;

   srand((int)time(NULL));
   compare_callback.function = _CompareInt;
   compare_callback.user_data = NULL;
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   binary_heap = BinaryHeap_Create(sizeof(int), compare_callback);
   if (!binary_heap) {
      fprintf(stderr, "BinaryHeap_Create() failed\n");
      return 1;
   }
   printf("BinaryHeap_Create() passed\n");

   BinaryHeap_Traverse(binary_heap, unary_callback);
   printf("\nBinaryHeap_Traverse() passed\n");
   BinaryHeap_Destroy(binary_heap);
   printf("BinaryHeap_Destroy() passed\n");
   printf("All binary-heap tests passed!\n");

   return 0;
}

static int _CompareInt(const void *data1, const void *data2, void *user_data)
{
   (void)user_data;
   if (*(int *)data1 < *(int *)data2) return -1;
   if (*(int *)data1 > *(int *)data2) return 1;
   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
