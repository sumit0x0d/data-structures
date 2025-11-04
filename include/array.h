#ifndef DATA_STRUCTURES_ARRAY_H
#define DATA_STRUCTURES_ARRAY_H

#include <stddef.h>

typedef struct Array * Array;
// typedef struct ArrayIterator * ArrayIterator;

// typedef enum {
//      ARRAY_SEARCH_LINEAR = 1,
//      ARRAY_SEARCH_BINARY = 2
// } ARRAY_SEARCH;

// typedef enum {
//      ARRAY_SORT_BUBBLE = 1,
//      ARRAY_SORT_SELECTION = 2,
//      ARRAY_SORT_INSERTION = 3,
//      ARRAY_SORT_QUICK = 4,
//      ARRAY_SORT_MERGE = 5,
// } ARRAY_SORT;

typedef enum {
     ARRAY_COMPARE_LESS = -1,
     ARRAY_COMPARE_EQUAL = 0,
     ARRAY_COMPARE_GREATER = 1
} ArrayCompare;

typedef struct {
     ArrayCompare (*function)(const void *data1, const void *data2, void *user_data);
     void *user_data;
} ArrayCompareCallback;

typedef struct {
     void (*function)(void *data, void *user_data);
     void *user_data;
} ArrayUnaryCallback;

typedef struct {
     size_t (*function)(const void *data, size_t size, void *user_data);
     void *user_data;
} ArrayHashCallback;

__attribute__((visibility("default")))
Array Array_Create(size_t data_size, size_t capacity);

__attribute__((visibility("default")))
void Array_Destroy(Array this);

__attribute__((visibility("default")))
size_t Array_GetCapacity(const Array this);

__attribute__((visibility("default")))
size_t Array_GetDataSize(const Array this);

__attribute__((visibility("default")))
void *Array_GetData(const Array this, size_t index);

__attribute__((visibility("default")))
void Array_SetData(Array this, size_t index, const void *data);

__attribute__((visibility("default")))
void Array_SwapData(Array this, void *data1, void *data2);

__attribute__((visibility("default")))
void Array_Traverse(Array this, ArrayUnaryCallback unary_callback);

__attribute__((visibility("default")))
void *Array_SearchLinear(const Array this, const void *data, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void *Array_SearchBinary(const Array this, const void *data, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void Array_SortBubble(Array this, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void Array_SortInsertion(Array this, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void Array_SortSelection(Array this, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void Array_SortQuick(Array this, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void Array_SortMerge(Array this, ArrayCompareCallback compare_callback);

__attribute__((visibility("default")))
void *Array_PatternSearchNaive(const Array this, const void *pattern, size_t pattern_size);

__attribute__((visibility("default")))
void *Array_PatternSearchRabinKarp(const Array this, const void *pattern,
     size_t pattern_size, ArrayHashCallback hash_callback);

__attribute__((visibility("default")))
void *Array_PatternSearchKmp(const Array this, const void *pattern, size_t pattern_size);

#endif
