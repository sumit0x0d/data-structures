#include <stdlib.h>
#include <string.h>

#include <dynamic-array.h>

struct DynamicArray {
     void *base;
     size_t data_size;
     size_t size;
     size_t capacity;
     double growth_factor;
};

DynamicArray DynamicArray_Create(size_t data_size, size_t capacity, double growth_factor)
{
     DynamicArray this;

     if (growth_factor > 1) {
          return NULL;
     }
     
     this = (DynamicArray)malloc(sizeof (struct DynamicArray));
     if (!this) {
          return NULL;
     }
     
     this->base = malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };
     
     this->data_size = data_size;
     this->growth_factor = growth_factor;
     this->capacity = capacity;
     
     return this;
}

void DynamicArray_Destroy(DynamicArray this)
{
     free(this->base);
     free(this);
}

size_t DynamicArray_GetSize(DynamicArray this)
{
     return this->size;
}

size_t DynamicArray_GetCapacity(DynamicArray this)
{
     return this->capacity;
}

void *DynamicArray_GetData(DynamicArray this, size_t index)
{
	return (char *)this->base + (this->data_size * index);
}

void *DynamicArray_GetBackData(DynamicArray this)
{
     return (char *)this->base + (this->data_size * this->size);
}

void DynamicArray_PushBack(DynamicArray this, const void *data)
{
     void *base;

     if (this->size == this->capacity) {
          this->capacity = this->capacity * this->growth_factor;
          base = realloc(this->base, this->data_size * this->capacity);
          if (!base) {
               return;
          }
          this->base = base;
     }
     
     memcpy(DynamicArray_GetData(this, this->size), data, this->data_size);
     this->size++;
}

void DynamicArray_PopBack(DynamicArray this)
{
     void *base;
     
     if (this->size == this->capacity) {
          this->capacity = this->capacity / this->growth_factor;
          base = realloc(this->base, this->data_size * this->capacity);
          if (!base) {
               return;
          }
          this->base = base;
     }

     this->size--;
}

void DynamicArray_Traverse(DynamicArray this, DynamicArrayUnaryCallback unary_callback)
{
     size_t i;

     for (i = 0; i < this->size; i++) {
          unary_callback.function(DynamicArray_GetData(this, i), unary_callback.user_data);
     }
}