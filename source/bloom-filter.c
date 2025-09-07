#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <bloom-filter.h>

typedef BloomFilterHash Hash;

struct bloom_filter {
     Array *array;
     Hash hash;
};

BloomFilter *BloomFilter_Create(DS_Size size, DS_Size bCount, Hash hash)
{
     BloomFilter *bFilter = (BloomFilter *)malloc(sizeof (BloomFilter));
     assert(bFilter);
     bFilter->array = Array_Create(size, bCount);
     assert(bFilter->array);
     bFilter->hash = hash;
     return bFilter;
}

void BloomFilter_Destroy(BloomFilter *bFilter)
{
     Array_Destroy(bFilter->array);
     free(bFilter);
}

DS_Bool BloomFilter_Search(BloomFilter *bFilter, const DS_Data data)
{
     return Array_GetData(bFilter->array, bFilter->hash(data, Array_GetSize(bFilter->array)));
}

void BloomFilter_Insert(BloomFilter *bFilter, const DS_Data data)
{
     Array_SetData(bFilter->array, bFilter->hash(data, Array_GetSize(bFilter->array)), data);
}
