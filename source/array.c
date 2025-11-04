#include <string.h>
#include <stdlib.h>

#include <array.h>

struct Array {
     DS_Generic base;
     DS_Size data_size;
     DS_Size capacity;
     DS_Generic swap_buffer;
};

Array Array_Create(DS_Size data_size, DS_Size capacity)
{
     Array this;

     this = (Array)malloc(sizeof (struct Array));
     if (!this) {
          return NULL;
     }

     this->base = (DS_Generic)malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->swap_buffer = (DS_Generic)malloc(data_size);
     if (!this->swap_buffer) {
          free(this->base);
          free(this);
          return NULL;
     }

     this->data_size = data_size;
     this->capacity = capacity;

     return this;
}

DS_Void Array_Destroy(Array this)
{
     free(this->swap_buffer);
     free(this->base);
     free(this);
}

DS_Size Array_GetCapacity(const Array this)
{
     return this->capacity;
}

DS_Size Array_GetDataSize(const Array this)
{
     return this->data_size;
}

DS_Generic Array_GetData(const Array this, DS_Size index)
{
     return (DS_Int8 *)this->base + (this->data_size * index);
}

DS_Void Array_SetData(Array this, DS_Size index, const DS_Generic data)
{
     memcpy(Array_GetData(this, index), data, this->data_size);
}

DS_Void Array_SwapData(Array this, DS_Generic data1, DS_Generic data2)
{
     memcpy(this->swap_buffer, data1, this->data_size);
     memcpy(data1, data2, this->data_size);
     memcpy(data2, this->swap_buffer, this->data_size);
}

DS_Void Array_Traverse(Array this, DS_UnaryCallback unary_callback)
{
     DS_Size i;

     for (i = 0; i < this->capacity; i++) {
          unary_callback.function(Array_GetData(this, i), unary_callback.user_data);
     }
}

DS_Generic Array_SearchLinear(const Array this, const DS_Generic data, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Generic current;

     for (i = 0; i < this->capacity; i++) {
          current = Array_GetData(this, i);
          if (compare_callback.function(current, data, compare_callback.user_data) == DS_COMPARE_EQUAL) {
               return current;
          }
     }

    return NULL;
}

DS_Generic Array_SearchBinary(const Array this, const DS_Generic data, DS_CompareCallback compare_callback)
{
     DS_Size left;
     DS_Size right;
     DS_Size middle;
     DS_Generic current;

     left = 0;
     right = this->capacity - 1;
     while (left < right) {
          middle = left + (right - left) / 2;
          current = Array_GetData(this, middle);
          switch (compare_callback.function(current, data, compare_callback.user_data)) {
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

DS_Void Array_SortBubble(Array this, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = this->capacity - 1; i > 0; i--) {
          for (j = 0; j < i; j++) {
               data1 = Array_GetData(this, j);
               data2 = Array_GetData(this, j + 1);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == DS_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

DS_Void Array_SortInsertion(Array this, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 1; i < this->capacity; i++) {
          j = i;
          do {
               data1 = Array_GetData(this, j - 1);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == DS_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
               j--;
          } while(j > 0);
     }
}

DS_Void Array_SortSelection(Array this, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size minimum;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < this->capacity - 1; i++) {
          minimum = i;
          for (j = minimum + 1; j < this->capacity; j++) {
               data1 = Array_GetData(this, minimum);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == DS_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

DS_Void Array_SortQuick(Array this, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < this->capacity - 1; i++) {
          for (j = i + 1; j < this->capacity - i; j++) {
               data1 = Array_GetData(this, i);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == DS_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

DS_Void Array_SortMerge(Array this, DS_CompareCallback compare_callback)
{
     DS_Size i;
     DS_Size j;
     DS_Generic data1;
     DS_Generic data2;

     for (i = 0; i < this->capacity - 1; i++) {
          for (j = i + 1; j < this->capacity - i; j++) {
               data1 = Array_GetData(this, i);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) ==  DS_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

DS_Generic Array_PatternSearchRabinKarp(const Array this, const DS_Generic pattern,
     DS_Size pattern_size, DS_HashCallback hash_callback)
{
     (DS_Void)this;
     (DS_Void)pattern;
     (DS_Void)pattern_size;
     (DS_Void)hash_callback;
     return NULL;
}
