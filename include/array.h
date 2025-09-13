#ifndef DATA_STRUCTURES_Array_H
#define DATA_STRUCTURES_Array_H

#include "data-structures.h"

typedef struct array * Array;

DS_PUBLIC_API
Array Array_Create(DS_Size sData, DS_Size capacity);

DS_PUBLIC_API
void Array_Destroy(Array array);

DS_PUBLIC_API
DS_Size Array_GetSize(const Array array);

DS_PUBLIC_API
DS_Size Array_GetDataSize(const Array array);

DS_PUBLIC_API
DS_Data Array_GetData(const Array array, DS_Size index);

DS_PUBLIC_API
void Array_SetSize(Array array, DS_Size size);

DS_PUBLIC_API
void Array_SetData(Array array, DS_Size index, const DS_Data data);

DS_PUBLIC_API
void Array_SwapData(Array array, DS_Data data1, DS_Data data2);

DS_PUBLIC_API
void Array_Traverse(Array array, DS_FunctionTraverse aTraverse, DS_Context context);

DS_PUBLIC_API
DS_Data Array_SearchLinear(const Array array, const DS_Data data, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
DS_Data Array_SearchBinary(const Array array, const DS_Data data, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
void Array_SortBubble(Array array, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
void Array_SortInsertion(Array array, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
void Array_SortSelection(Array array, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
void Array_SortQuick(Array array, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
void Array_SortMerge(Array array, DS_FunctionCompare fCompare, DS_Context context);

DS_PUBLIC_API
DS_Data Array_PatternSearchNaive(const Array array, const DS_Data pattern, DS_Size sPattern);

DS_PUBLIC_API
DS_Data Array_PatternSearchRabinKarp(const Array array, const DS_Data pattern, DS_Size sPattern,
                                     DS_FunctionHash fHash, DS_Context context);

DS_PUBLIC_API
DS_Data Array_PatternSearchKnuthMorrisPratt(const Array array, const DS_Data pattern, DS_Size sPattern);

#endif
