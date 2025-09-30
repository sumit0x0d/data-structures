#include <stdlib.h>
#include <string.h>

#include <array.h>

struct array {
     DS_Generic base;
     DS_Size data_size;
     DS_Size size;
     DS_Generic swap_buffer;
};

Array Array_Create(DS_Size data_size, DS_Size size)
{
     Array array = (Array)malloc(sizeof (struct array));
     if (!array) {
          return NULL;
     }
     array->base = malloc(data_size * size);
     if (array->base) {
          free(array);
          return NULL;
     };
     array->swap_buffer = malloc(data_size);
     if (!array->swap_buffer) {
          free(array->base);
          free(array);
          return NULL;
     }
     array->data_size = data_size;
     array->size = size;
     return array;
}

DS_Void Array_Destroy(Array array)
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

DS_Void Array_SetSize(Array array, DS_Size size)
{
     DS_Generic base = realloc(array->base, array->data_size * size);
     if (!base) {
          return;
     }
     array->base = base;
     array->size = size;
}

inline DS_Generic Array_GetData(const Array array, DS_Size index)
{
     return (DS_Int8 *)array->base + (array->data_size * index);
}

DS_Void Array_SetData(Array array, DS_Size index, const DS_Generic data)
{
     memcpy(Array_GetData(array, index), data, array->data_size);
}

DS_Void Array_SwapData(Array array, DS_Generic data1, DS_Generic data2)
{
     memcpy(array->swap_buffer, data1, array->data_size);
     memcpy(data1, data2, array->data_size);
     memcpy(data2, array->swap_buffer, array->data_size);
}

DS_Void Array_Traverse(Array array, DS_CallbackUnary unary_callback, DS_Generic context)
{
     for (DS_Size i = 0; i < array->size; i++) {
          unary_callback(Array_GetData(array, i), context);
     }
}

DS_Generic Array_SearchLinear(const Array array, const DS_Generic data, DS_CallbackCompare compare_callback,
                           DS_Generic compare_context)
{
     for (DS_Size i = 0; i < array->size; i++)
     {
          DS_Generic current = Array_GetData(array, i);
          if (compare_callback(current, data, compare_context) == 0) {
               return current;
          }
     }
     return NULL;
}

DS_Generic Array_SearchBinary(const Array array, const DS_Generic data, DS_CallbackCompare compare_callback, DS_Generic compare_context)
{
     DS_Size left = 0;
     DS_Size right = array->size;
     while (left < right) {
          DS_Size middle = left + (right - left) / 2;
          DS_Generic current = Array_GetData(array, middle);
          switch (compare_callback(current, data, compare_context)) {
          case DS_COMPARE_LESS:
               left = middle + 1;
               break;
          case DS_COMPARE_EQUAL:
               return current;
          case DS_COMPARE_GREATER:
               right = middle;
               break;
          }
     }
     return NULL;
}

DS_Void Array_SortBubble(Array array, DS_CallbackCompare compare_callback, DS_Generic context)
{
     for (DS_Size i = array->size - 1; i > 0; i--) {
          for (DS_Size j = 0; j < i; j++) {
               DS_Generic data1 = Array_GetData(array, j);
               DS_Generic data2 = Array_GetData(array, j + 1);
               if (compare_callback(data1, data2, context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

DS_Void Array_SortInsertion(Array array, DS_CallbackCompare compare, DS_Generic compare_context)
{
     for (DS_Size i = 1; i < array->size; i++) {
          DS_Size j = i;
          do {
               DS_Generic data1 = Array_GetData(array, j - 1);
               DS_Generic data2 = Array_GetData(array, j);
               if (compare(data1, data2, compare_context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
               j--;
          } while(j > 0);
     }
}

DS_Void Array_SortSelection(Array array, DS_CallbackCompare compare, DS_Generic compare_context)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          DS_Size minimum = i;
          for (DS_Size j = minimum + 1; j < array->size; j++) {
               DS_Generic data1 = Array_GetData(array, minimum);
               DS_Generic data2 = Array_GetData(array, j);
               if (compare(data1, data2, compare_context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

DS_Void Array_SortQuick(Array array, DS_CallbackCompare compare, DS_Generic compare_context)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Generic data1 = Array_GetData(array, i);
               DS_Generic data2 = Array_GetData(array, j);
               if (compare(data1, data2, compare_context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

DS_Void Array_SortMerge(Array array, DS_CallbackCompare compare, DS_Generic compare_context)
{
     for (DS_Size i = 0; i < array->size - 1; i++) {
          for (DS_Size j = i + 1; j < array->size - i; j++) {
               DS_Generic data1 = Array_GetData(array, i);
               DS_Generic data2 = Array_GetData(array, j);
               if (compare(data1, data2, compare_context) == DS_COMPARE_GREATER) {
                    Array_SwapData(array, data1, data2);
               }
          }
     }
}

DS_Generic Array_PatternSearchRabinKarp(const Array array, const DS_Generic pattern, DS_Size sPattern,
                                        DS_CallbackHash hash_callback, DS_Generic hash_context)
{
     (DS_Void)array;
     (DS_Void)pattern;
     (DS_Void)sPattern;
     (DS_Void)hash_callback;
     (DS_Void)hash_context;
     return NULL;
}
