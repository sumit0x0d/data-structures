#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <bloom-filter.h>

struct bloom_filter {
     Array array;
     DS_CallbackCompare hash_callback;
     DS_Generic hash_context;
};

BloomFilter BloomFilter_Create(DS_Size size, DS_Size bCount, DS_CallbackCompare hash_callback, DS_Generic hash_context)
{
     BloomFilter bFilter = (BloomFilter *)malloc(sizeof (BloomFilter));
     if (!bFilter) {
          return NULL;
     }
     bFilter->array = Array_Create(size, bCount);
     if (!bFilter->array) {
          free(bFilter);
          return NULL;
     }
     bFilter->hash_callback = hash_callback;
     bFilter->hash_context = hash_context;
     return bFilter;
}

DS_Void BloomFilter_Destroy(BloomFilter bFilter)
{
     Array_Destroy(bFilter->array);
     free(bFilter);
}

DS_Bool BloomFilter_Search(BloomFilter bFilter, const DS_Generic data)
{
     DS_Size index =  bFilter->hash_callback(data, Array_GetSize(bFilter->array), bFilter->hash_context);
     return Array_GetData(bFilter->array, index);
}

DS_Void BloomFilter_Insert(BloomFilter bFilter, const DS_Generic data)
{
     DS_Size index = bFilter->hash_callback(data, Array_GetSize(bFilter->array), bFilter->hash_context);
     Array_SetData(bFilter->array, index, data);
}
