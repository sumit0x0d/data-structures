#ifndef DATA_STRUCTURES_ARRAY_H
#define DATA_STRUCTURES_ARRAY_H

#include "data-structures.h"

typedef struct Array * Array;
// typedef struct ArrayIterator * ArrayIterator;

// typedef enum {
//      ARRAY_SEARCH_LINEAR = 1,
//      ARRAY_SEARCH_BINARY = 2
// } ARRAY_SEARCH;

// typedef enum {
//      ARRAY_SORT_BUBBLE    = 1,
//      ARRAY_SORT_SELECTION = 2,
//      ARRAY_SORT_INSERTION = 3,
//      ARRAY_SORT_QUICK     = 4,
//      ARRAY_SORT_MERGE     = 5,
// } ARRAY_SORT;

DATA_STRUCTURES_API
Array Array_Create(DS_Size data_size, DS_Size capacity);

DATA_STRUCTURES_API
DS_Void Array_Destroy(Array this);

DATA_STRUCTURES_API
DS_Size Array_GetCapacity(const Array this);

DATA_STRUCTURES_API
DS_Size Array_GetDataSize(const Array this);

DATA_STRUCTURES_API
DS_Generic Array_GetData(const Array this, DS_Size index);

DATA_STRUCTURES_API
DS_Void Array_SetData(Array this, DS_Size index, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void Array_SwapData(Array this, DS_Generic data1, DS_Generic data2);

DATA_STRUCTURES_API
DS_Void Array_Traverse(Array this, DS_UnaryCallback unary_callback);

DATA_STRUCTURES_API
DS_Generic Array_SearchLinear(const Array this, const DS_Generic data, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Generic Array_SearchBinary(const Array this, const DS_Generic data, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void Array_SortBubble(Array this, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void Array_SortInsertion(Array this, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void Array_SortSelection(Array this, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void Array_SortQuick(Array this, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void Array_SortMerge(Array this, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Generic Array_PatternSearchNaive(const Array this, const DS_Generic pattern, DS_Size pattern_size);

DATA_STRUCTURES_API
DS_Generic Array_PatternSearchRabinKarp(const Array this, const DS_Generic pattern,
     DS_Size pattern_size, DS_HashCallback hash_callback);

DATA_STRUCTURES_API
DS_Generic Array_PatternSearchKmp(const Array this, const DS_Generic pattern, DS_Size pattern_size);

#endif
