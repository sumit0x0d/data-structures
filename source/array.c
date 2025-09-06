#include <stdlib.h>
#include <string.h>

#include <array.h>

struct array {
     void *base;
     DS_Size data_size;
     DS_Size size;
};

Array *DS_Array_Create(DS_Size size, DS_Size capacity)
{
     Array *array = (Array *)malloc(sizeof (Array));
     if (!array) {
          LOGGING_SYSTEM_LOG_ERROR("Memory allocation failed");
          return NULL;
     }
     array->base = malloc(size * capacity);
     if (array->base) {
          free(array);
          return NULL;
     };
     array->data_size = size;
     array->size = capacity;
     return array;
}

void DS_Array_Destroy(Array *array)
{
     free(array->base);
     free(array);
}

DS_Size DS_Array_GetSize(const Array *array)
{
     return array->size;
}

DS_Size DS_Array_GetDataSize(const Array *array)
{
     return array->data_size;
}

void DS_Array_SetSize(Array *array, DS_Size size)
{
     void *base = realloc(array->base, array->data_size * size);
     if (!base) {
          return;
     }
     array->base = base;
     array->size = size;
}

inline void *DS_Array_GetData(const Array *array, DS_Size index)
{
     return (char *)array->base + (array->data_size * index);
}

void DS_Array_SetData(Array *array, DS_Size index, const DS_Data data)
{
     memcpy(DS_Array_GetData(array, index), data, array->data_size);
}

void DS_Array_SwapData(Array *array, DS_Data data1, DS_Data data2, void *tData)
{
     memcpy(tData, data1, array->data_size);
     memcpy(data1, data2, array->data_size);
     memcpy(data2, tData, array->data_size);
}

void DS_Array_Traverse(Array *array, DS_FunctionTraverse traverse, void *uData)
{
     for (DS_Size i = 0; i < array->size; i++) {
          traverse(DS_Array_GetData(array, i), uData);
     }
}

void *DS_Array_SearchLinear(const Array *array, const DS_Data data, DS_FunctionCompare compare, void *uData)
{
     for (DS_Size i = 0; i < array->size; i++) {
          void *tData = DS_Array_GetData(array, i);
          if (compare(tData, data, uData) == 0) {
               return tData;
          }
     }
     return NULL;
}

void *DS_Array_SearchBinary(const Array *array, const DS_Data data, DS_FunctionCompare compare, void *uData)
{
     for (DS_Size i = 0; i < array->size; i++) {
          void *tData = DS_Array_GetData(array, i);
          if (compare(tData, data, uData) == 0) {
               return tData;
          }
     }
     return NULL;
}

void DS_Array_SortBubble(Array *array, DS_FunctionCompare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     if (!tData) {
          return;
     };
     for (DS_Size i = array->size - 1; i > 0; i--) {
          for (DS_Size j = 0; j < i; j++) {
               DS_Data data1 = DS_Array_GetData(array, j);
               DS_Data data2 = DS_Array_GetData(array, j + 1);
               if (compare(data1, data2, uData) == 1) {
                    DS_Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void DS_Array_SortInsertion(Array *array, DS_FunctionCompare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     if (tData) {
          return;
     };
     for (DS_Size i = 1; i < array->size; i++) {
          DS_Size j = i;
          do {
               DS_Data data1 = DS_Array_GetData(array, j - 1);
               DS_Data data2 = DS_Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    DS_Array_SwapData(array, data1, data2, tData);
               }
               j--;
          } while(j > 0);
     }
     free(tData);
}

void DS_Array_SortSelection(Array *array, DS_FunctionCompare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     if (tData) {
          return;
     };
     for (DS_Size i = 0; i < array->size - 1; i++) {
          DS_Size minimum = i;
          for (DS_Size j = minimum + 1; j < array->size; j++) {
               DS_Data data1 = DS_Array_GetData(array, minimum);
               DS_Data data2 = DS_Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    DS_Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void DS_Array_SortQuick(Array *array, DS_FunctionCompare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     if (tData) {
          return;
     };
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Data data1 = DS_Array_GetData(array, i);
               DS_Data data2 = DS_Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    DS_Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void DS_Array_SortMerge(Array *array, DS_FunctionCompare compare, void *uData)
{
     void *tData = malloc(array->data_size);
     if (tData) {
          return;
     };
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Data data1 = DS_Array_GetData(array, i);
               DS_Data data2 = DS_Array_GetData(array, j);
               if (compare(data1, data2, uData) == 1) {
                    DS_Array_SwapData(array, data1, data2, tData);
               }
          }
     }
     free(tData);
}

void *DS_Array_PatternSearchRabinKarp(const Array *array, const void *pattern, DS_Size pSize, DS_FunctionHash hash, void *uData)
{
     (void)array;
     (void)pattern;
     (void)pSize;
     (void)hash;
     (void)uData;
     return NULL;
}
