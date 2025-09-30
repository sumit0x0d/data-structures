#ifndef DATA_STRUCTURES_Array_H
#define DATA_STRUCTURES_Array_H

#include "data-structures.h"

typedef struct array * Array;

DS_API
Array Array_Create(DS_Size data_size, DS_Size size);

DS_API
DS_Void Array_Destroy(Array array);

DS_API
DS_Size Array_GetSize(const Array array);

DS_API
DS_Size Array_GetDataSize(const Array array);

DS_API
DS_Generic Array_GetData(const Array array, DS_Size index);

DS_API
DS_Void Array_SetSize(Array array, DS_Size size);

DS_API
DS_Void Array_SetData(Array array, DS_Size index, const DS_Generic data);

DS_API
DS_Void Array_SwapData(Array array, DS_Generic data1, DS_Generic data2);

DS_API
DS_Void Array_Traverse(Array array, DS_CallbackUnary unary_callback, DS_Generic unary_context);

DS_API
DS_Generic Array_SearchLinear(const Array array, const DS_Generic data, DS_CallbackCompare compare_callback,
                              DS_Generic compare_context);

DS_API
DS_Generic Array_SearchBinary(const Array array, const DS_Generic data, DS_CallbackCompare compare_callback,
                              DS_Generic compare_context);

DS_API
DS_Void Array_SortBubble(Array array, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void Array_SortInsertion(Array array, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void Array_SortSelection(Array array, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void Array_SortQuick(Array array, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void Array_SortMerge(Array array, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Generic Array_PatternSearchNaive(const Array array, const DS_Generic pattern, DS_Size sPattern);

DS_API
DS_Generic Array_PatternSearchRabinKarp(const Array array, const DS_Generic pattern, DS_Size pattern_size,
                                        DS_CallbackHash hash_callback, DS_Generic hash_context);

DS_API
DS_Generic Array_PatternSearchKnuthMorrisPratt(const Array array, const DS_Generic pattern, DS_Size pattern_size);

#endif
