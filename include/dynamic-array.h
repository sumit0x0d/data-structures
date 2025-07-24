#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct dynamic_array DynamicArray;
typedef void (*DynamicArrayTraverse)(void *data, void *uData);

DynamicArray *DynamicArray_Create(size_t dSize, size_t capacity, double gFactor);
void DynamicArray_Destroy(DynamicArray *dArray);

size_t DynamicArray_GetSize(DynamicArray *dArray);
void *DynamicArray_GetData(DynamicArray *dArray, size_t index);
void *DynamicArray_GetBackData(DynamicArray *dArray);

void DynamicArray_PushBack(DynamicArray *dArray, const void *data);
void DynamicArray_PopBack(DynamicArray *dArray);

void DynamicArray_Traverse(DynamicArray *dArray, DynamicArrayTraverse daTraverse, void *uData);

#endif
