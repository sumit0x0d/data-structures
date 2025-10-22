#include <stdlib.h>
#include <string.h>

#include <array.h>

struct Array {
     DS_Generic base;
     DS_Size data_size;
     DS_Size size;
     DS_Generic swap_buffer;
};

Array Array_Create( DS_Size data_size, DS_Size size)
{
     Array self;

     self = (Array)malloc(sizeof (struct Array));
     if (!self) {
          return NULL;
     }

     self->base = malloc(data_size * size);
     if (!self->base) {
          free(self);
          return NULL;
     };

     self->swap_buffer = malloc(data_size);
     if (!self->swap_buffer) {
          free(self->base);
          free(self);
          return NULL;
     }

     self->data_size = data_size;
     self->size = size;

     return self;
}

DS_Void Array_Destroy(Array self)
{
     free(self->swap_buffer);
     free(self->base);
     free(self);
}

DS_Size Array_GetSize(const Array self)
{
     return self->size;
}

DS_Size Array_GetDataSize(const Array self)
{
     return self->data_size;
}

DS_Void Array_SetSize( Array self, DS_Size size)
{
     DS_Generic base;

     base = realloc(self->base, self->data_size * size);
     if (!base) {
          return;
     }

     self->base = base;
     self->size = size;
}

DS_Generic Array_GetData( const Array self, DS_Size index)
{
     return (DS_Int8 *)self->base + (self->data_size * index);
}

DS_Void Array_SetData(Array self, DS_Size index, const DS_Generic data)
{
     memcpy(Array_GetData(self, index), data, self->data_size);
}

DS_Void Array_SwapData(Array self, DS_Generic data1, DS_Generic data2)
{
     memcpy(self->swap_buffer, data1, self->data_size);
     memcpy(data1, data2, self->data_size);
     memcpy(data2, self->swap_buffer, self->data_size);
}

DS_Void Array_Traverse(Array self, DS_UnaryCallback unary_callback)
{
     DS_Size i;

     for (i = 0; i < self->size; i++) {
          unary_callback.function(Array_GetData(self, i), unary_callback.context);
     }
}

DS_Generic Array_SearchLinear(const Array self, const DS_Generic data, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Generic current;

     for (i = 0; i < self->size; i++) {
          current = Array_GetData(self, i);
          if (compare_callback.function(current, data, compare_callback.context) == DS_COMPARE_EQUAL) {
               return current;
          }
     }

    return NULL;
}

DS_Generic Array_SearchBinary(const Array self, const DS_Generic data, DS_CompareCallback compare_callback)
{
     DS_Size left;
     DS_Size right;
     DS_Size middle;
     DS_Generic current;
     
     left = 0;
     right = self->size;
     while (left < right) {
          middle = left + (right - left) / 2;
          current = Array_GetData(self, middle);
          switch (compare_callback.function(current, data, compare_callback.context)) {
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

DS_Void Array_SortBubble(Array self, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = self->size - 1; i > 0; i--) {
          for (j = 0; j < i; j++) {
               data1 = Array_GetData(self, j);
               data2 = Array_GetData(self, j + 1);
               if (compare_callback.function(data1, data2, compare_callback.context) == DS_COMPARE_GREATER) {
                    Array_SwapData(self, data1, data2);
               }
          }
     }
}

DS_Void Array_SortInsertion(Array self, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 1; i < self->size; i++) {
          j = i;
          do {
               data1 = Array_GetData(self, j - 1);
               data2 = Array_GetData(self, j);
               if (compare_callback.function(data1, data2, compare_callback.context) == DS_COMPARE_GREATER) {
                    Array_SwapData(self, data1, data2);
               }
               j--;
          } while(j > 0);
     }
}

DS_Void Array_SortSelection(Array self, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size minimum;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < self->size - 1; i++) {
          minimum = i;
          for (j = minimum + 1; j < self->size; j++) {
               data1 = Array_GetData(self, minimum);
               data2 = Array_GetData(self, j);
               if (compare_callback.function(data1, data2, compare_callback.context) == DS_COMPARE_GREATER) {
                    Array_SwapData(self, data1, data2);
               }
          }
     }
}

DS_Void Array_SortQuick(Array self, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < self->size - 1; i++) {
          for (j = i + 1; j < self->size - i; j++) {
               data1 = Array_GetData(self, i);
               data2 = Array_GetData(self, j);
               if (compare_callback.function(data1, data2, compare_callback.context) == DS_COMPARE_GREATER) {
                    Array_SwapData(self, data1, data2);
               }
          }
     }
}

DS_Void Array_SortMerge(Array self, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < self->size - 1; i++) {
          for (j = i + 1; j < self->size - i; j++) {
               data1 = Array_GetData(self, i);
               data2 = Array_GetData(self, j);
               if (compare_callback.function(data1, data2, compare_callback.context) ==  DS_COMPARE_GREATER) {
                    Array_SwapData(self, data1, data2);
               }
          }
     }
}

DS_Generic Array_PatternSearchRabinKarp(const Array self, const DS_Generic pattern,
     DS_Size pattern_size, DS_HashCallback hash_callback)
{
     (DS_Void)self;
     (DS_Void)pattern;
     (DS_Void)pattern_size;
     (DS_Void)hash_callback;
     return NULL;
}
