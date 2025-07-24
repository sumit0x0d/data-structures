#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>

#define CAPACITY 30000

/*
 * Comparison callback for int.
 *
 * @param data1 : Pointer to the first int.
 * @param data2 : Pointer to the second int.
 * @return      : -1 if *data1 < *data2, 0 if *data1 == *data2, 1 if *data1 > *data2.
 */
static int _compare_int(const void *data1, const void *data2, void *uData);

/*
 * Hash function for integers within an array context.
 *
 * @param[0] data  : Pointer to the integer data to hash.
 * @param[1] aSize : Size of the array (upper bound for index).
 * @return         : Index in the range [0, aSize).
 */
static size_t _hash_int(const void *data, size_t aSize, void *uData);

/*
 * Traverse callback that print integers.
 *
 * @param[0] data : Pointer to the integer to be printed.
 */
static void _traverse_print(void *data, void *uData);

int main()
{
     srand((int)time(NULL));
     Array *array = Array_Create(sizeof(int), CAPACITY);
     assert(array != NULL);
     assert(Array_GetSize(array) == 0);
     assert(Array_GetDataSize(array) == sizeof(int));
     printf("array_create() passed\n");
     for (int i = 0; i < CAPACITY; i++) {
          int value = rand() % 100;
          Array_SetData(array, i, &value);
     }    
     printf("array_set_data() passed\n");
     Array_PatternSearchRabinKarp(array, NULL, 0, _hash_int, NULL);
     Array_Traverse(array, _traverse_print, NULL);
     printf("\narray_traverse() passed\n");
     // Array_SortBubble(array, _compare_int, NULL);
     Array_SortInsertion(array, _compare_int, NULL);
     Array_SortSelection(array, _compare_int, NULL);
     Array_Traverse(array, _traverse_print, NULL);
     printf("\narray_traverse() passed\n");
     Array_Destroy(array);
     printf("array_destroy() passed\n");
     printf("All array tests passed!\n");
     return 0;
}

static int _compare_int(const void *data1, const void *data2, void *uData)
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

static size_t _hash_int(const void *data, size_t aSize, void *uData)
{
     (void)uData;
     return (*(int *)data) % aSize;
}

static void _traverse_print(void *data, void *uData)
{
     (void)uData;
     printf("%d ", *(int *)data);
}
