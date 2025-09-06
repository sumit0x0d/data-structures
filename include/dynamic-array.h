#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct dynamic_array DynamicArray;

DS_PUBLIC_API
DynamicArray *DS_DynamicArray_Create(DS_Size sData, DS_Size daCapacity, DS_Float64 gFactor);

DS_PUBLIC_API
void DS_DynamicArray_Destroy(DynamicArray *array);

DS_PUBLIC_API
DS_Size DS_DynamicArray_GetSize(DynamicArray *array);

DS_PUBLIC_API
DS_Data DS_DynamicArray_GetData(DynamicArray *array, DS_Size index);

DS_PUBLIC_API
DS_Data DS_DynamicArray_GetBackData(DynamicArray *array);

DS_PUBLIC_API
void DS_DynamicArray_PushBack(DynamicArray *array, const DS_Data data);

DS_PUBLIC_API
void DS_DynamicArray_PopBack(DynamicArray *array);

DS_PUBLIC_API
void DS_DynamicArray_Traverse(DynamicArray *array, DS_FunctionTraverse fTraverse, DS_Data dTemporary);

#endif
