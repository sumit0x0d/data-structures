#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct DynamicArray * DynamicArray;

DATA_STRUCTURES_API
DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size size, DS_Float64 growth_factor);

DATA_STRUCTURES_API
DS_Void DynamicArray_Destroy(DynamicArray self);

DATA_STRUCTURES_API
DS_Size DynamicArray_GetSize(DynamicArray self);

DATA_STRUCTURES_API
DS_Generic DynamicArray_GetData(DynamicArray self, DS_Size index);

DATA_STRUCTURES_API
DS_Generic DynamicArray_GetBackData(DynamicArray self);

DATA_STRUCTURES_API
DS_Void DynamicArray_PushBack(DynamicArray self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void DynamicArray_PopBack(DynamicArray self);

DATA_STRUCTURES_API
DS_Void DynamicArray_Traverse(DynamicArray self, DS_UnaryCallback unary_callback);

#endif