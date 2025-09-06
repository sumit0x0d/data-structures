#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define CAPACITY 30000


static int _compare_int(const DS_Data data1, const DS_Data data2, void *uData);
static DS_Size _hash_int(const DS_Data data, DS_Size aSize, void *uData);
static void _traverse_print(DS_Data data, void *uData);

int main()
{
     srand((int)time(NULL));
     Array *array = DS_Array_Create(sizeof(int), CAPACITY);
     assert(array != NULL);
     assert(DS_Array_GetSize(array) == 0);
     assert(DS_Array_GetDataSize(array) == sizeof(int));
     printf("DS_Array_create() passed\n");
     for (int i = 0; i < CAPACITY; i++) {
          int value = rand() % 100;
          DS_Array_SetData(array, i, &value);
     }    
     printf("DS_Array_set_data() passed\n");
     DS_Array_PatternSearchRabinKarp(array, NULL, 0, _hash_int, NULL);
     DS_Array_Traverse(array, _traverse_print, NULL);
     printf("\nDS_Array_traverse() passed\n");
     // DS_Array_SortBubble(array, _compare_int, NULL);
     DS_Array_SortInsertion(array, _compare_int, NULL);
     DS_Array_SortSelection(array, _compare_int, NULL);
     DS_Array_Traverse(array, _traverse_print, NULL);
     printf("\nDS_Array_traverse() passed\n");
     DS_Array_Destroy(array);
     printf("DS_Array_destroy() passed\n");
     printf("All array tests passed!\n");
     return 0;
}

static int _compare_int(const DS_Data data1, const DS_Data data2, void *uData)
{
     (void)uData;
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     return 0;
}

static DS_Size _hash_int(const DS_Data data, DS_Size aSize, void *uData)
{
     (void)uData;
     return (*(int *)data) % aSize;
}

static void _traverse_print(DS_Data data, void *uData)
{
     (void)uData;
     printf("%d ", *(int *)data);
}
