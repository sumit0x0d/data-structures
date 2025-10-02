#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define size 30000


static int _CallbackCompareInt(const DS_Generic data1, const DS_Generic data2, DS_Generic context);
static DS_Size _CallbackHashInt(const DS_Generic data, DS_Size aSize, DS_Generic context);
static DS_Void _CallbackUnaryPrint(DS_Generic data, DS_Generic context);

int main()
{
    srand((int)time(NULL));
    Array *array = Array_Create(sizeof(int), size);
    assert(array != NULL);
    assert(Array_GetSize(array) == 0);
    assert(Array_GetDataSize(array) == sizeof(int));
    printf("Array_create() passed\n");
    for (int i = 0; i < size; i++) {
        int value = rand() % 100;
        Array_SetData(array, i, &value);
    }    
    printf("Array_set_data() passed\n");
    Array_PatternSearchRabinKarp(array, NULL, 0, _CallbackCompareInt, NULL);
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

static int _CallbackCompareInt(const DS_Generic data1, const DS_Generic data2, DS_Generic compare_context)
{
    (DS_Void)compare_context;
    if (*(int *)data1 < *(int *)data2) {
        return -1;
    }
    if (*(int *)data1 > *(int *)data2) {
        return 1;
    }
    return 0;
}

static DS_Size _CallbackHashInt(const DS_Generic data, DS_Size aSize, DS_Generic hash_context)
{
    (DS_Void)hash_context;
    return (*(int *)data) % aSize;
}

static DS_Void _CallbackUnaryPrint(DS_Generic data, DS_Generic uanry_context)
{
    (DS_Void)uanry_context;
    printf("%d ", *(int *)data);
}
