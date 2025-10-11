#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define SIZE 300

static DS_Compare _CallbackCompareInt(
     const DS_Generic data1,
     const DS_Generic data2,
     DS_Generic       compare_context
);
static DS_Void _CallbackUnaryPrint(
     DS_Generic data,
     DS_Generic unary_context
);

int main(
     void
) {
     Array array;
     
     srand((int)time(NULL));

     array = Array_Create(sizeof(int), SIZE);
     if (array == NULL) {
          fprintf(stderr, "Array_create() failed\n");
          return 1;
     }
     
     printf("Array_create() passed\n");
     
     for (int i = 0; i < SIZE; i++) {
          int value = rand() % 100;
          Array_SetData(array, i, &value);
     }
     
     printf("Array_set_data() passed\n");
     Array_Traverse(array, _CallbackUnaryPrint, NULL);
     printf("\nArray_traverse() passed\n");
     // Array_SortBubble(array, _compare_int, NULL);
     Array_SortInsertion(array, _CallbackCompareInt, NULL);
     Array_SortSelection(array, _CallbackCompareInt, NULL);
     Array_Traverse(array, _CallbackUnaryPrint, NULL);
     printf("\nArray_traverse() passed\n");
     Array_Destroy(array);
     printf("Array_destroy() passed\n");
     printf("All array tests passed!\n");
     
     return 0;
}

static DS_Compare _CallbackCompareInt(
     const DS_Generic data1,
     const DS_Generic data2,
     DS_Generic       compare_context
) {
     (DS_Void)compare_context;
     
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     
     return 0;
}

// static DS_Size _CallbackHashInt(const DS_Generic data, DS_Size aSize, DS_Generic hash_context)
// {
//     (DS_Void)hash_context;
//     return (*(int *)data) % aSize;
// }

static DS_Void _CallbackUnaryPrint(
     DS_Generic data,
     DS_Generic uanry_context
) {
     (DS_Void)uanry_context;
     printf("%d ", *(int *)data);
}
