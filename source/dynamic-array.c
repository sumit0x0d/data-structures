#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <dynamic-array.h>

struct DynamicArray {
     Array array;
     DS_Size size;
     DS_Float64 growth_factor;
};

DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size size, DS_Float64 growth_factor)
{
     DynamicArray self;

     if (growth_factor > 1) {
          return NULL;
     }
     
     self = (DynamicArray)malloc(sizeof (struct DynamicArray));
     if (!self) {
          return NULL;
     }
     
     self->array = Array_Create(data_size, size);
     if (!self->array) {
          free(self);
          return NULL;
     }
     
     self->growth_factor = growth_factor;
     
     return self;
}

DS_Void DynamicArray_Destroy(DynamicArray self)
{
     Array_Destroy(self->array);
     free(self);
}

DS_Size DynamicArray_GetSize(DynamicArray self)
{
     return self->size;
}

DS_Generic DynamicArray_GetData(DynamicArray self, DS_Size index)
{
	return Array_GetData(self->array, index);
}

DS_Generic DynamicArray_GetBackData(DynamicArray self)
{
     return Array_GetData(self->array, self->size);
}

DS_Void DynamicArray_PushBack(DynamicArray self, const DS_Generic data)
{
     DS_Size size;

     size = Array_GetSize(self->array);
     if (self->size == size) {
          Array_SetSize(self->array, size * self->growth_factor);
     }
     
     Array_SetData(self->array, self->size, data);
}

DS_Void DynamicArray_PopBack(DynamicArray self)
{
     DS_Size size;
     
     size = Array_GetSize(self->array);
     if (self->size == size / self->growth_factor) {
          Array_SetSize(self->array, size / self->growth_factor);
     }
     
     self->size--;
}

DS_Void DynamicArray_Traverse(DynamicArray self, DS_UnaryCallback unary_callback)
{
     DS_Size i;

     for (i = 0; i < Array_GetSize(self->array); i++) {
          unary_callback.function(DynamicArray_GetData(self, i), unary_callback.context);
     }
}
