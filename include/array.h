#ifndef DATA_STRUCTURES_ARRAY_H
#define DATA_STRUCTURES_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct array Array;
typedef void (*ArrayTraverse)(void *data, void *uData);
typedef int (*ArrayCompare)(const void *data1, const void *data2, void *uData);
typedef size_t (*ArrayHash)(const void *data, size_t dSize, void *uData);

/*
 * Hash function for integers within an array context.
 *
 * @param[0] dSize    : data_size
 * @param[1] capacity : Maximum capacity
 * @return            : Array
 */
Array *Array_Create(size_t dSize, size_t capacity);
void Array_Destroy(Array *array);

size_t Array_GetSize(const Array *array);
size_t Array_GetDataSize(const Array *array);
void *Array_GetData(const Array *array, size_t index);

void Array_SetSize(Array *array, size_t size);
void Array_SetData(Array *array, size_t index, const void *data);
void Array_SwapData(Array *array, void *data1, void *data2, void *tData);

void Array_Traverse(Array *array, ArrayTraverse aTraverse, void *uData);
void *Array_SearchLinear(const Array *array, const void *data, ArrayCompare aCompare, void *uData);
void *Array_SearchBinary(const Array *array, const void *data, ArrayCompare aCompare, void *uData);

void Array_SortBubble(Array *array, ArrayCompare aCompare, void *uData);
void Array_SortInsertion(Array *array, ArrayCompare aCompare, void *uData);
void Array_SortSelection(Array *array, ArrayCompare aCompare, void *uData);
void Array_SortQuick(Array *array, ArrayCompare aCompare, void *uData);
void Array_SortMerge(Array *array, ArrayCompare aCompare, void *uData);

void *Array_PatternSearchNaive(const Array *array, const void *pattern, size_t pSize);
void *Array_PatternSearchRabinKarp(const Array *array, const void *pattern, size_t pSize, ArrayHash aHash, void *uData);
void *Array_PatternSearchKnuthMorrisPratt(const Array *array, const void *pattern, size_t pSize);

#endif
