#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define CAPACITY 30000


static int _compare_int(const DS_Data data1, const DS_Data data2, DS_Context context);
static DS_Size _hash_int(const DS_Data data, DS_Size aSize, DS_Context context);
static DS_Void _traverse_print(DS_Data data, DS_Context context);

int main()
{
     srand((int)time(NULL));
     Array *array = Array_Create(sizeof(int), CAPACITY);
     assert(array != NULL);
     assert(Array_GetSize(array) == 0);
     assert(Array_GetDataSize(array) == sizeof(int));
     printf("Array_create() passed\n");
     for (int i = 0; i < CAPACITY; i++) {
          int value = rand() % 100;
          Array_SetData(array, i, &value);
     }    
     printf("Array_set_data() passed\n");
     Array_PatternSearchRabinKarp(array, NULL, 0, _hash_int, NULL);
     Array_Traverse(array, _traverse_print, NULL);
     printf("\nArray_traverse() passed\n");
     // Array_SortBubble(array, _compare_int, NULL);
     Array_SortInsertion(array, _compare_int, NULL);
     Array_SortSelection(array, _compare_int, NULL);
     Array_Traverse(array, _traverse_print, NULL);
     printf("\nArray_traverse() passed\n");
     Array_Destroy(array);
     printf("Array_destroy() passed\n");
     printf("All array tests passed!\n");
     return 0;
}

static int _compare_int(const DS_Data data1, const DS_Data data2, DS_Context context)
{
     (DS_Void)uData;
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     return 0;
}

static DS_Size _hash_int(const DS_Data data, DS_Size aSize, DS_Context context)
{
     (DS_Void)uData;
     return (*(int *)data) % aSize;
}

static DS_Void _traverse_print(DS_Data data, DS_Context context)
{
     (DS_Void)uData;
     printf("%d ", *(int *)data);
}
