#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <dynamic-array.h>

typedef DynamicArrayTraverse Traverse;

struct dynamic_array {
     Array *array;
     size_t size;
     double growth_factor;
};

DynamicArray *DynamicArray_Create(size_t dSize, size_t capacity, double gFactor)
{
     assert(gFactor > 1);
     DynamicArray *dArray = (DynamicArray *)malloc(sizeof (DynamicArray));
     assert(dArray);
     dArray->array = Array_Create(dSize, capacity);
     assert(dynamic_array->array);
     dArray->growth_factor = gFactor;
     return dArray;
}

void DynamicArray_Destroy(DynamicArray *dArray)
{
     Array_Destroy(dArray->array);
     free(dArray);
}

size_t DynamicArray_GetSize(DynamicArray *dArray)
{
     return dArray->size;
}

void *DynamicArray_GetData(DynamicArray *dArray, size_t index)
{
	return Array_GetData(dArray->array, index);
}

void *DynamicArray_GetBackData(DynamicArray *dArray)
{
     return Array_GetData(dArray->array, dArray->size);
}

void DynamicArray_PushBack(DynamicArray *dArray, const void *data)
{
     size_t aSize = Array_GetSize(dArray->array);
     if (dArray->size == aSize) {
          Array_SetSize(dArray->array, aSize * dArray->growth_factor);
     }
     Array_SetData(dArray->array, dArray->size, data);
}

void DynamicArray_PopBack(DynamicArray *dArray)
{
     size_t aSize = Array_GetSize(dArray->array);
     if (dArray->size == aSize / dArray->growth_factor) {
          Array_SetSize(dArray->array, aSize / dArray->growth_factor);
     }
     dArray->size--;
}

void DynamicArray_Traverse(DynamicArray *dArray, Traverse traverse, void *uData)
{
     for (size_t i = 0; i < Array_GetSize(dArray->array); i++) {
          traverse(DynamicArray_GetData(dArray, i), uData);
     }
}
