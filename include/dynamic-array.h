#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

typedef struct DynamicArray DynamicArray;
typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} DynamicArrayUnaryCallback;

__attribute__((visibility("default")))
DynamicArray *DynamicArray_Create(size_t data_size, size_t capacity, double growth_factor);

__attribute__((visibility("default")))
void DynamicArray_Destroy(DynamicArray *this);

__attribute__((visibility("default")))
size_t DynamicArray_GetCapacity(DynamicArray *this);

__attribute__((visibility("default")))
void *DynamicArray_GetData(DynamicArray *this, size_t index);

__attribute__((visibility("default")))
void *DynamicArray_GetBackData(DynamicArray *this);

__attribute__((visibility("default")))
void DynamicArray_PushBack(DynamicArray *this, const void *data);

__attribute__((visibility("default")))
void DynamicArray_PopBack(DynamicArray *this);

__attribute__((visibility("default")))
void DynamicArray_Traverse(DynamicArray *this, DynamicArrayUnaryCallback unary_callback);

#endif