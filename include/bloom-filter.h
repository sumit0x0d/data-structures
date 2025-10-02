#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <data-structures.h>

typedef struct BloomFilter * BloomFilter;

DS_API
BloomFilter BloomFilter_Create(DS_Size data_size, DS_Size bucket_count,
    DS_CallbackHash hash_callback, DS_Generic hash_context);

DS_API
DS_Void BloomFilter_Destroy(BloomFilter bloom_filter);

DS_API
DS_Generic BloomFilter_Search(BloomFilter bloom_filter, const DS_Generic data);

DS_API
DS_Void BloomFilter_Insert(BloomFilter bloom_filter, const DS_Generic data);

#endif
