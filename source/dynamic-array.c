#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <dynamic-array.h>

struct dynamic_array {
     Array *array;
     DS_Size size;
     DS_Float64 growth_factor;
};

DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size capacity, DS_Float64 gFactor)
{
     if (gFactor > 1) {
          return NULL;
     }
     DynamicArray array = (DynamicArray)malloc(sizeof (struct dynamic_array));
     if (!array) {
          return NULL;
     }
     array->array = Array_Create(data_size, capacity);
     if (!array->array) {
          free(array);
          return NULL;
     }
     array->growth_factor = gFactor;
     return array;
}

DS_Void DynamicArray_Destroy(DynamicArray array)
{
     Array_Destroy(array->array);
     free(array);
}

DS_Size DynamicArray_GetSize(DynamicArray array)
{
     return array->size;
}

DS_Void *DynamicArray_GetData(DynamicArray array, DS_Size index)
{
	return Array_GetData(array->array, index);
}

DS_Void *DynamicArray_GetBackData(DynamicArray array)
{
     return Array_GetData(array->array, array->size);
}

DS_Void DynamicArray_PushBack(DynamicArray array, const DS_Data data)
{
     DS_Size aSize = Array_GetSize(array->array);
     if (array->size == aSize) {
          Array_SetSize(array->array, aSize * array->growth_factor);
     }
     Array_SetData(array->array, array->size, data);
}

DS_Void DynamicArray_PopBack(DynamicArray array)
{
     DS_Size aSize = Array_GetSize(array->array);
     if (array->size == aSize / array->growth_factor) {
          Array_SetSize(array->array, aSize / array->growth_factor);
     }
     array->size--;
}

DS_Void DynamicArray_Traverse(DynamicArray array, DS_FunctionUnary traverse, DS_Data dTemporary)
{
     for (DS_Size i = 0; i < Array_GetSize(array->array); i++) {
          traverse(DynamicArray_GetData(array, i), dTemporary);
     }
}
