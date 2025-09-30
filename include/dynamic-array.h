#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct dynamic_array * DynamicArray;

DS_API
DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size size, DS_Float64 growth_factor);

DS_API
DS_Void DynamicArray_Destroy(DynamicArray array);

DS_API
DS_Size DynamicArray_GetSize(DynamicArray array);

DS_API
DS_Generic DynamicArray_GetData(DynamicArray array, DS_Size index);

DS_API
DS_Generic DynamicArray_GetBackData(DynamicArray array);

DS_API
DS_Void DynamicArray_PushBack(DynamicArray array, const DS_Generic data);

DS_API
DS_Void DynamicArray_PopBack(DynamicArray array);

DS_API
DS_Void DynamicArray_Traverse(DynamicArray array, DS_CallbackUnary unary_callback, DS_Generic unary_context);

#endif
