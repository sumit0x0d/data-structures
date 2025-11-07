#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define SIZE 300

static ArrayCompare _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
     Array *array;
     
     srand((int)time(NULL));

     array = Array_Create(sizeof(int), SIZE);
     if (array == NULL) {
          fprintf(stderr, "Array_Create() failed\n");
          return 1;
     }
     
     printf("Array_Create() passed\n");
     
     for (int i = 0; i < SIZE; i++) {
          int value = rand() % 100;
          Array_SetData(array, i, &value);
     }
     
     printf("Array_set_data() passed\n");
     
     
     ArrayCompareCallback compare_callback = {
          .function = _CompareInt,
          .user_data = NULL
     };

     ArrayUnaryCallback unary_callback = {
          .function = _UnaryPrint,
          .user_data = NULL
     };
     Array_Traverse(array, unary_callback);
     printf("\nArray_traverse() passed\n");
     // Array_SortBubble(array, _compare_int, NULL);
     Array_SortInsertion(array, compare_callback);
     Array_SortSelection(array, compare_callback);
     Array_Traverse(array, unary_callback);
     printf("\nArray_traverse() passed\n");
     
     Array_Destroy(array);
     printf("Array_Destroy() passed\n");
     printf("All array tests passed!\n");
     
     return 0;
}

static ArrayCompare _CompareInt(const void *data1, const void *data2, void *user_data)
{
     (void)user_data;
     
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     
     return 0;
}

// static size_t _CallbackHashInt(const void *data, size_t aSize, void *hash_callback.user_data)
// {
//     (void)hash_callback.user_data;
//     return (*(int *)data) % aSize;
// }

static void _UnaryPrint(void *data, void *user_data)
{
     (void)user_data;
     printf("%d ", *(int *)data);
}
