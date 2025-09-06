#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <data-structures.h>
#include <array.h>

typedef struct bloom_filter BloomFilter;
typedef DS_Size (*BloomFilterHash)(const DS_Data data, DS_Size cBucket);

DS_PUBLIC_API
BloomFilter *BloomFilter_Create(DS_Size sData, DS_Size cBucket, BloomFilterHash bfHash);

DS_PUBLIC_API
void BloomFilter_Destroy(BloomFilter *bFilter);

DS_PUBLIC_API
DS_Bool BloomFilter_Search(BloomFilter *bFilter, const DS_Data data);

DS_PUBLIC_API
void Bloom_Filter_Insert(BloomFilter *bFilter, const DS_Data data);

#endif
