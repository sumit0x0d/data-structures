#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct DynamicArray * DynamicArray;

DATA_STRUCTURES_API
DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size capacity, DS_Float64 growth_factor);

DATA_STRUCTURES_API
DS_Void DynamicArray_Destroy(DynamicArray this);

DATA_STRUCTURES_API
DS_Size DynamicArray_GetCapacity(DynamicArray this);

DATA_STRUCTURES_API
DS_Generic DynamicArray_GetData(DynamicArray this, DS_Size index);

DATA_STRUCTURES_API
DS_Generic DynamicArray_GetBackData(DynamicArray this);

DATA_STRUCTURES_API
DS_Void DynamicArray_PushBack(DynamicArray this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DynamicArray_PopBack(DynamicArray this);

DATA_STRUCTURES_API
DS_Void DynamicArray_Traverse(DynamicArray this, DS_UnaryCallback unary_callback);

#endif