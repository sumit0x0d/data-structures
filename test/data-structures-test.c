#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define SIZE 300

static DS_Compare _CompareInt(const DS_Generic data1, const DS_Generic data2, DS_Generic context);
static DS_Void _UnaryPrint(DS_Generic data, DS_Generic context);

int main(void)
{
     Array array;
     
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
     
     
     DS_CompareCallback compare_callback = {
          .function = _CompareInt,
          .context = NULL
     };

     DS_UnaryCallback unary_callback = {
          .function = _UnaryPrint,
          .context = NULL
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

static DS_Compare _CompareInt(const DS_Generic data1, const DS_Generic data2, DS_Generic context)
{
     (DS_Void)context;
     
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     
     return 0;
}

// static DS_Size _CallbackHashInt(const DS_Generic data, DS_Size aSize, DS_Generic hash_callback.context)
// {
//     (DS_Void)hash_callback.context;
//     return (*(int *)data) % aSize;
// }

static DS_Void _UnaryPrint(DS_Generic data, DS_Generic context)
{
     (DS_Void)context;
     printf("%d ", *(int *)data);
}
