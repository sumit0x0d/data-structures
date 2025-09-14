#include <stdlib.h>
#include <string.h>

#include <array.h>

struct array {
     DS_Data base;
     DS_Size data_size;
     DS_Size size;
     DS_Data swap_buffer;
};

Array Array_Create(DS_Size sData, DS_Size capacity)
{
     Array array = (Array)malloc(sizeof (struct array));
     if (!array) {
          return NULL;
     }
     array->base = malloc(sData * capacity);
     if (array->base) {
          free(array);
          return NULL;
     };
     array->swap_buffer = malloc(sData);
     if (!array->swap_buffer) {
          free(array->base);
          free(array);
          return NULL;
     }
     array->data_size = sData;
     array->size = capacity;
     return array;
}

void Array_Destroy(Array array)
{
     free(array->swap_buffer);
     free(array->base);
     free(array);
}

DS_Size Array_GetSize(const Array array)
{
     return array->size;
}

DS_Size Array_GetDataSize(const Array array)
{
     return array->data_size;
}

void Array_SetSize(Array array, DS_Size size)
{
     DS_Data base = realloc(array->base, array->data_size * size);
     if (!base) {
          return;
     }
     array->base = base;
     array->size = size;
}

inline DS_Data Array_GetData(const Array array, DS_Size index)
{
     return (DS_Int8 *)array->base + (array->data_size * index);
}

void Array_SetData(Array array, DS_Size index, const DS_Data data)
{
     memcpy(Array_GetData(array, index), data, array->data_size);
}

void Array_SwapData(Array array, DS_Data data1, DS_Data data2)
{
     memcpy(array->swap_buffer, data1, array->data_size);
     memcpy(data1, data2, array->data_size);
     memcpy(data2, array->swap_buffer, array->data_size);
}

void Array_Traverse(Array array, DS_FunctionTraverse fTraverse, DS_Context context)
{
     for (DS_Size i = 0; i < array->size; i++) {
          fTraverse(Array_GetData(array, i), context);
     }
}

DS_Data Array_SearchLinear(const Array array, const DS_Data data, DS_FunctionCompare compare, DS_Context cCompare)
{
     for (DS_Size i = 0; i < array->size; i++) {
          DS_Data dCurrent = Array_GetData(array, i);
          if (compare(dCurrent, data, cCompare) == 0) {
               return dCurrent;
          }
     }
     return NULL;
}

DS_Data Array_SearchBinary(const Array array, const DS_Data data, DS_FunctionCompare fCompare, DS_Context cCompare)
{
     DS_Size dLeft = 0;
     DS_Size dRight = array->size;
     while (dLeft < dRight) {
          DS_Size dMiddle = dLeft + (dRight - dLeft) / 2;
          DS_Data dCurrent = Array_GetData(array, dMiddle);
          switch (fCompare(dCurrent, data, cCompare)) {
          case DS_COMPARE_LESS:
               dLeft = dMiddle + 1;
               break;
          case DS_COMPARE_EQUAL:
               return dCurrent;
          case DS_COMPARE_GREATER:
               dRight = dMiddle;
               break;
          }
     }
     return NULL;
}

void Array_SortBubble(Array array, DS_FunctionCompare fCompare, DS_Context context)
{
     for (DS_Size i = array->size - 1; i > 0; i--) {
          for (DS_Size j = 0; j < i; j++) {
               DS_Data data1 = Array_GetData(array, j);
               DS_Data data2 = Array_GetData(array, j + 1);
               if (fCompare(data1, data2, context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

void Array_SortInsertion(Array array, DS_FunctionCompare compare, DS_Context cCompare)
{
     for (DS_Size i = 1; i < array->size; i++) {
          DS_Size j = i;
          do {
               DS_Data data1 = Array_GetData(array, j - 1);
               DS_Data data2 = Array_GetData(array, j);
               if (compare(data1, data2, cCompare) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
               j--;
          } while(j > 0);
     }
}

void Array_SortSelection(Array array, DS_FunctionCompare compare, DS_Context cCompare)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          DS_Size minimum = i;
          for (DS_Size j = minimum + 1; j < array->size; j++) {
               DS_Data data1 = Array_GetData(array, minimum);
               DS_Data data2 = Array_GetData(array, j);
               if (compare(data1, data2, cCompare) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

void Array_SortQuick(Array array, DS_FunctionCompare compare, DS_Context cCompare)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Data data1 = Array_GetData(array, i);
               DS_Data data2 = Array_GetData(array, j);
               if (compare(data1, data2, cCompare) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

void Array_SortMerge(Array array, DS_FunctionCompare compare, DS_Context cCompare)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Data data1 = Array_GetData(array, i);
               DS_Data data2 = Array_GetData(array, j);
               if (compare(data1, data2, cCompare) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

DS_Data Array_PatternSearchRabinKarp(const Array array, const DS_Data pattern, DS_Size sPattern,
                                     DS_FunctionHash fHash, DS_Context cHash)
{
     (void)array;
     (void)pattern;
     (void)sPattern;
     (void)fHash;
     (void)cHash;
     return NULL;
}
