#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <dynamic-array.h>

struct DynamicArray {
     Array      array;
     DS_Size    size;
     DS_Float64 growth_factor;
};

DynamicArray DynamicArray_Create(
     DS_Size    data_size,
     DS_Size    size,
     DS_Float64 growth_factor
) {
     DynamicArray dynamic_array;

     if (growth_factor > 1) {
          return NULL;
     }
     
     dynamic_array = (DynamicArray)malloc(sizeof (struct DynamicArray));
     if (!dynamic_array) {
          return NULL;
     }
     
     dynamic_array->array = Array_Create(data_size, size);
     if (!dynamic_array->array) {
          free(dynamic_array);
          return NULL;
     }
     
     dynamic_array->growth_factor = growth_factor;
     
     return dynamic_array;
}

DS_Void DynamicArray_Destroy(
     DynamicArray dynamic_array
) {
     Array_Destroy(dynamic_array->array);
     free(dynamic_array);
}

DS_Size DynamicArray_GetSize(
     DynamicArray dynamic_array
) {
     return dynamic_array->size;
}

DS_Generic DynamicArray_GetData(
     DynamicArray dynamic_array,
     DS_Size      index
) {
	return Array_GetData(dynamic_array->array, index);
}

DS_Generic DynamicArray_GetBackData(
     DynamicArray dynamic_array
) {
     return Array_GetData(dynamic_array->array, dynamic_array->size);
}

DS_Void DynamicArray_PushBack(
     DynamicArray     dynamic_array,
     const DS_Generic data
) {
     DS_Size size;

     size = Array_GetSize(dynamic_array->array);
     if (dynamic_array->size == size) {
          Array_SetSize(dynamic_array->array, size * dynamic_array->growth_factor);
     }
     
     Array_SetData(dynamic_array->array, dynamic_array->size, data);
}

DS_Void DynamicArray_PopBack(
     DynamicArray dynamic_array
) {
     DS_Size size;
     
     size = Array_GetSize(dynamic_array->array);
     if (dynamic_array->size == size / dynamic_array->growth_factor) {
          Array_SetSize(dynamic_array->array, size / dynamic_array->growth_factor);
     }
     
     dynamic_array->size--;
}

DS_Void DynamicArray_Traverse(
     DynamicArray     dynamic_array,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
) {
     DS_Size i;

     for (i = 0; i < Array_GetSize(dynamic_array->array); i++) {
          unary_callback(DynamicArray_GetData(dynamic_array, i), unary_context);
     }
}
