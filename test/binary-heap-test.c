#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <binary-heap.h>

static int _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   BinaryHeap *obj;
   int i, value;
   BinaryHeapCompareCallback compare_callback;
   BinaryHeapUnaryCallback unary_callback;

   srand((int)time(NULL));
   compare_callback.function = _CompareInt;
   compare_callback.user_data = NULL;
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = BinaryHeap_Create(sizeof(int), compare_callback);
   if (!obj) {
      fprintf(stderr, "BinaryHeap_Create() failed\n");
      return 1;
   }
   printf("BinaryHeap_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      BinaryHeap_Insert(heap, &value);
   }
   printf("BinaryHeap_Insert() passed\n");
   BinaryHeap_Traverse(heap, unary_callback);
   printf("\nBinaryHeap_Traverse() passed\n");
   BinaryHeap_Destroy(heap);
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
