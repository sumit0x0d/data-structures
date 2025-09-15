#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct dynamic_array * DynamicArray;

DS_API
DynamicArray DynamicArray_Create(DS_Size sData, DS_Size size, DS_Float64 gFactor);

DS_API
void DynamicArray_Destroy(DynamicArray array);

DS_API
DS_Size DynamicArray_GetSize(DynamicArray array);

DS_API
DS_Data DynamicArray_GetData(DynamicArray array, DS_Size index);

DS_API
DS_Data DynamicArray_GetBackData(DynamicArray array);

DS_API
void DynamicArray_PushBack(DynamicArray array, const DS_Data data);

DS_API
void DynamicArray_PopBack(DynamicArray array);

DS_API
void DynamicArray_Traverse(DynamicArray array, DS_FunctionUnary fUnary, DS_Context cUnary);

#endif
