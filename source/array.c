#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>

typedef ArrayTraverse Traverse;
typedef ArrayCompare Compare;
typedef ArrayHash Hash;

struct array {
     void *base;
     size_t data_size;
     size_t size;
};

Array *Array_Create(size_t dSize, size_t capacity)
{
     Array *array = (Array *)malloc(sizeof (Array));
     assert(array);
     array->base = malloc(dSize * capacity);
     assert(array->base);
     array->data_size = dSize;
     array->size = capacity;
     return array;
}

void Array_Destroy(Array *array)
{
     free(array->base);
     free(array);
}

size_t Array_GetSize(const Array *array)
{
     return array->size;
}

size_t Array_GetDataSize(const Array *array)
{
     return array->data_size;
}

void Array_SetSize(Array *array, size_t size)
{
     void *base = realloc(array->base, array->data_size * size);
     assert(base);
     array->base = base;
     array->size = size;
}

inline void *Array_GetData(const Array *array, size_t index)
{
     return (char *)array->base + (array->data_size * index);
}

void Array_SetData(Array *array, size_t index, const void *data)
{
     memcpy(Array_GetData(array, index), data, array->data_size);
}

void Array_SwapData(Array *array, void *data1, void *data2, void *tData)
{
     memcpy(tData, data1, array->data_size);
     memcpy(data1, data2, array->data_size);
     memcpy(data2, tData, array->data_size);
}

void Array_Traverse(Array *array, Traverse traverse, void *uData)
{
     for (size_t i = 0; i < array->size; i++) {
          traverse(Array_GetData(array, i), uData);
     }
}

void *Array_SearchLinear(const Array *array, const void *data, Compare compare, void *uData)
{
     for (size_t i = 0; i < array->size; i++) {
          void *tData = Array_GetData(array, i);
          if (compare(tData, data, uData) == 0) {
               return tData;
          }
     }
     return NULL;
}

void *Array_SearchBinary(const Array *array, const void *data, Compare compare, void *uData)
{
     for (size_t i = 0; i < array->size; i++) {
          void *tData = Array_GetData(array, i);
          if (compare(tData, data, uData) == 0) {
               return tData;
          }
     }
     return NULL;
}

void Array_SortBubble(Array *array, Compare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     assert(tData);
     for (size_t i = array->size - 1; i > 0; i--) {
          for (size_t j = 0; j < i; j++) {
               void *data1 = Array_GetData(array, j);
               void *data2 = Array_GetData(array, j + 1);
               if (compare(data1, data2, uData) == 1) {
                    Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void Array_SortInsertion(Array *array, Compare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     assert(tdata);
     for (size_t i = 1; i < array->size; i++) {
          size_t j = i;
          do {
               void *data1 = Array_GetData(array, j - 1);
               void *data2 = Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    Array_SwapData(array, data1, data2, tData);
               }
               j--;
          } while(j > 0);
     }
     free(tData);
}

void Array_SortSelection(Array *array, Compare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     assert(tdata);
     for (size_t i = 0; i < array->size - 1; i++) {
          size_t minimum = i;
          for (size_t j = minimum + 1; j < array->size; j++) {
               void *data1 = Array_GetData(array, minimum);
               void *data2 = Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void Array_SortQuick(Array *array, Compare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     assert(tdata);
     for (size_t i = 0; i < array->size - 1; i++) {
          for (size_t j = i + 1; j < array->size - i; j++) {
               void *data1 = Array_GetData(array, i);
               void *data2 = Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void Array_SortMerge(Array *array, Compare compare, void *uData)
{
     void *tdata = malloc(array->data_size);
     assert(tdata);
     for (size_t i = 0; i < array->size - 1; i++) {
          for (size_t j = i + 1; j < array->size - i; j++) {
               void *data1 = Array_GetData(array, i);
               void *data2 = Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    Array_SwapData(array, data1, data2, tdata);
               }
          }
     }
     free(tdata);
}

void *Array_PatternSearchRabinKarp(const Array *array, const void *pattern, size_t pSize, Hash hash, void *uData)
{
     (void)array;
     (void)pattern;
     (void)pSize;
     (void)hash;
     (void)uData;
     return NULL;
}
