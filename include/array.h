#ifndef DATA_STRUCTURES_Array_H
#define DATA_STRUCTURES_Array_H

#include "data-structures.h"

typedef struct array Array;

DS_PUBLIC_API
Array *DS_Array_Create(DS_Size sData, DS_Size capacity);

DS_PUBLIC_API
void DS_Array_Destroy(Array *array);

DS_PUBLIC_API
DS_Size DS_Array_GetSize(const Array *array);

DS_PUBLIC_API
DS_Size DS_Array_GetDataSize(const Array *array);

DS_PUBLIC_API
DS_Data DS_Array_GetData(const Array *array, DS_Size index);

DS_PUBLIC_API
void DS_Array_SetSize(Array *array, DS_Size sData);

DS_PUBLIC_API
void DS_Array_SetData(Array *array, DS_Size index, const DS_Data data);

DS_PUBLIC_API
void DS_Array_SwapData(Array *array, DS_Data data1, DS_Data data2, DS_Data dTemporary);

DS_PUBLIC_API
void DS_Array_Traverse(Array *array, DS_FunctionTraverse aTraverse, DS_Data dUser);

DS_PUBLIC_API
DS_Data DS_Array_SearchLinear(const Array *array, const DS_Data data, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
DS_Data DS_Array_SearchBinary(const Array *array, const DS_Data data, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_Array_SortBubble(Array *array, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_Array_SortInsertion(Array *array, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_Array_SortSelection(Array *array, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_Array_SortQuick(Array *array, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_Array_SortMerge(Array *array, DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
DS_Data DS_Array_PatternSearchNaive(const Array *array, const DS_Data pattern, DS_Size sPattern);

DS_PUBLIC_API
DS_Data DS_Array_PatternSearchRabinKarp(const Array *array, const DS_Data pattern, DS_Size sPattern, DS_FunctionHash fHash, DS_Data dUser);

DS_PUBLIC_API
DS_Data DS_Array_PatternSearchKnuthMorrisPratt(const Array *array, const DS_Data pattern, DS_Size sPattern);

#endif
