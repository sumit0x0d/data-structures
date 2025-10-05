#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <data-structures.h>

typedef struct BloomFilter * BloomFilter;

DATA_STRUCTURES_API
BloomFilter BloomFilter_Create(
     DS_Size         data_size,
     DS_Size         bucket_count,
     DS_CallbackHash hash_callback,
     DS_Generic      hash_context
);

DATA_STRUCTURES_API
DS_Void BloomFilter_Destroy(
     BloomFilter bloom_filter
);

DATA_STRUCTURES_API
DS_Generic BloomFilter_Search(
     BloomFilter      bloom_filter,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void BloomFilter_Insert(
     BloomFilter      bloom_filter,
     const DS_Generic data
);

#endif
