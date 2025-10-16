#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <bloom-filter.h>

struct BloomFilter {
     Array array;
     DS_CallbackHash hash_callback;
     DS_Generic hash_context;
};

BloomFilter BloomFilter_Create(
     DS_Size data_size,
     DS_Size bucket_count,
     DS_CallbackHash hash_callback,
     DS_Generic hash_context
) {
     BloomFilter bloom_filter;

     bloom_filter = (BloomFilter)malloc(sizeof (struct BloomFilter));
     if (!bloom_filter) {
          return NULL;
     }
     
     bloom_filter->array = Array_Create(data_size, bucket_count);
     if (!bloom_filter->array) {
          free(bloom_filter);
          return NULL;
     }
     
     bloom_filter->hash_callback = hash_callback;
     bloom_filter->hash_context = hash_context;
     
     return bloom_filter;
}

DS_Void BloomFilter_Destroy(
     BloomFilter bloom_filter
) {
     Array_Destroy(bloom_filter->array);
     free(bloom_filter);
}

DS_Generic BloomFilter_Search(
     BloomFilter bloom_filter,
     const DS_Generic data
) {
     DS_Size index;

     index = bloom_filter->hash_callback(
             data,
             Array_GetSize(bloom_filter->array),
             bloom_filter->hash_context);

     return Array_GetData(bloom_filter->array, index);
}

DS_Void BloomFilter_Insert(
     BloomFilter bloom_filter,
     const DS_Generic data
) {
     DS_Size index;

     index = bloom_filter->hash_callback(
             data,
             Array_GetSize(bloom_filter->array),
             bloom_filter->hash_context);

     Array_SetData(bloom_filter->array, index, data);
}
