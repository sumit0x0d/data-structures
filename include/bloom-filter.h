#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

#include <data-structures.h>

typedef struct bloom_filter * BloomFilter;

DS_API
BloomFilter BloomFilter_Create(DS_Size data_size, DS_Size bucket_count, DS_FunctionHash hash_function,
                               DS_Context hash_context);

DS_API
DS_Void BloomFilter_Destroy(BloomFilter bFilter);

DS_API
DS_Bool BloomFilter_Search(BloomFilter bFilter, const DS_Data data);

DS_API
DS_Void Bloom_Filter_Insert(BloomFilter bFilter, const DS_Data data);

#endif
