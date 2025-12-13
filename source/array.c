#include <string.h>
#include <stdlib.h>

#include <array.h>

struct Array {
     void *base;
     size_t data_size;
     size_t capacity;
     void *swap_buffer;
};

Array *Array_Create(size_t data_size, size_t capacity)
{
     Array *this;

     this = (Array *)malloc(sizeof (Array));
     if (!this) {
          return NULL;
     }

     this->base = malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->swap_buffer = malloc(data_size);
     if (!this->swap_buffer) {
          free(this->base);
          free(this);
          return NULL;
     }

     this->data_size = data_size;
     this->capacity = capacity;

     return this;
}

void Array_Destroy(Array *this)
{
     free(this->swap_buffer);
     free(this->base);
     free(this);
}

size_t Array_GetCapacity(const Array *this)
{
     return this->capacity;
}

size_t Array_GetDataSize(const Array *this)
{
     return this->data_size;
}

void *Array_GetData(const Array *this, size_t index)
{
     return (char *)this->base + (this->data_size * index);
}

void Array_SetData(Array *this, size_t index, const void *data)
{
     memcpy(Array_GetData(this, index), data, this->data_size);
}

void Array_SwapData(Array *this, void *data1, void *data2)
{
     memcpy(this->swap_buffer, data1, this->data_size);
     memcpy(data1, data2, this->data_size);
     memcpy(data2, this->swap_buffer, this->data_size);
}

void Array_Traverse(Array *this, ArrayUnaryCallback unary_callback)
{
     size_t i;

     for (i = 0; i < this->capacity; i++) {
          unary_callback.function(Array_GetData(this, i), unary_callback.user_data);
     }
}

void *Array_SearchLinear(const Array *this, const void *data, ArrayCompareCallback compare_callback)
{
     size_t i;
     void *current;

     for (i = 0; i < this->capacity; i++) {
          current = Array_GetData(this, i);
          if (compare_callback.function(current, data, compare_callback.user_data) == ARRAY_COMPARE_EQUAL) {
               return current;
          }
     }

    return NULL;
}

void *Array_SearchBinary(const Array *this, const void *data, ArrayCompareCallback compare_callback)
{
     size_t left;
     size_t right;
     size_t middle;
     void *current;

     left = 0;
     right = this->capacity - 1;
     while (left < right) {
          middle = left + (right - left) / 2;
          current = Array_GetData(this, middle);
          switch (compare_callback.function(current, data, compare_callback.user_data)) {
          case ARRAY_COMPARE_LESS:
               left = middle + 1;
               break;
          case ARRAY_COMPARE_EQUAL:
               return current;
          case ARRAY_COMPARE_GREATER:
               right = middle;
               break;
          }
     }

     return NULL;
}

void Array_SortBubble(Array *this, ArrayCompareCallback compare_callback)
{
     size_t i;
     size_t j;
     void *data1;
     void *data2;

     for (i = this->capacity - 1; i > 0; i--) {
          for (j = 0; j < i; j++) {
               data1 = Array_GetData(this, j);
               data2 = Array_GetData(this, j + 1);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == ARRAY_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

void Array_SortInsertion(Array *this, ArrayCompareCallback compare_callback)
{
     size_t i;
     size_t j;
     void *data1;
     void *data2;

     for (i = 1; i < this->capacity; i++) {
          j = i;
          do {
               data1 = Array_GetData(this, j - 1);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == ARRAY_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
               j--;
          } while(j > 0);
     }
}

void Array_SortSelection(Array *this, ArrayCompareCallback compare_callback)
{
     size_t i;
     size_t minimum;
     size_t j;
     void *data1;
     void *data2;

     for (i = 0; i < this->capacity - 1; i++) {
          minimum = i;
          for (j = minimum + 1; j < this->capacity; j++) {
               data1 = Array_GetData(this, minimum);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == ARRAY_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

void Array_SortQuick(Array *this, ArrayCompareCallback compare_callback)
{
     size_t i;
     size_t j;
     void *data1;
     void *data2;

     for (i = 0; i < this->capacity - 1; i++) {
          for (j = i + 1; j < this->capacity - i; j++) {
               data1 = Array_GetData(this, i);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) == ARRAY_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

void Array_SortMerge(Array *this, ArrayCompareCallback compare_callback)
{
     size_t i;
     size_t j;
     void *data1;
     void *data2;

     for (i = 0; i < this->capacity - 1; i++) {
          for (j = i + 1; j < this->capacity - i; j++) {
               data1 = Array_GetData(this, i);
               data2 = Array_GetData(this, j);
               if (compare_callback.function(data1, data2, compare_callback.user_data) ==  ARRAY_COMPARE_GREATER) {
                    Array_SwapData(this, data1, data2);
               }
          }
     }
}

void *Array_PatternSearchRabinKarp(const Array *this,
     const void *pattern, size_t pattern_size,
     ArrayHashCallback hash_callback)
{
     (void)this;
     (void)pattern;
     (void)pattern_size;
     (void)hash_callback;
     return NULL;
}
