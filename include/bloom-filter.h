#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <stdbool.h>
#include <stddef.h>

#include <array.h>

typedef struct bloom_filter BloomFilter;
typedef size_t (*BloomFilterHash)(const void *data, size_t bCount);

BloomFilter *BloomFilter_Create(size_t dSize, size_t bCount, BloomFilterHash bfHash);
void BloomFilter_Destroy(BloomFilter *bFilter);

bool BloomFilter_Search(BloomFilter *bFilter, const void *data);
void Bloom_Filter_Insert(BloomFilter *bFilter, const void *data);

#endif
