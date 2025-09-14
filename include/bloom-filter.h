#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <data-structures.h>

typedef struct bloom_filter * BloomFilter;

DS_PUBLIC_API
BloomFilter BloomFilter_Create(DS_Size sData, DS_Size nBucket, DS_FunctionHash fHash, DS_Context cHash);

DS_PUBLIC_API
void BloomFilter_Destroy(BloomFilter bFilter);

DS_PUBLIC_API
DS_Bool BloomFilter_Search(BloomFilter bFilter, const DS_Data data);

DS_PUBLIC_API
void Bloom_Filter_Insert(BloomFilter bFilter, const DS_Data data);

#endif
