#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <data-structures.h>

typedef struct DynamicArray * DynamicArray;

DS_API
DynamicArray DynamicArray_Create(DS_Size data_size, DS_Size size,
                                 DS_Float64 growth_factor);

DS_API
DS_Void DynamicArray_Destroy(DynamicArray dynamic_array);

DS_API
DS_Size DynamicArray_GetSize(DynamicArray dynamic_array);

DS_API
DS_Generic DynamicArray_GetData(DynamicArray dynamic_array, DS_Size index);

DS_API
DS_Generic DynamicArray_GetBackData(DynamicArray dynamic_array);

DS_API
DS_Void DynamicArray_PushBack(DynamicArray dynamic_array, const DS_Generic data);

DS_API
DS_Void DynamicArray_PopBack(DynamicArray dynamic_array);

DS_API
DS_Void DynamicArray_Traverse(DynamicArray dynamic_array,
                              DS_CallbackUnary unary_callback, DS_Generic unary_context);

#endif
