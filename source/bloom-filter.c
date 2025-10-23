#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <bloom-filter.h>

struct BloomFilter {
     Array array;
     DS_HashCallback hash_callback;
};

BloomFilter BloomFilter_Create(DS_Size data_size, DS_Size bucket_count, DS_HashCallback hash_callback)
{
     BloomFilter self;

     self = (BloomFilter)malloc(sizeof (struct BloomFilter));
     if (!self) {
          return NULL;
     }
     
     self->array = Array_Create(data_size, bucket_count);
     if (!self->array) {
          free(self);
          return NULL;
     }
     
     self->hash_callback = hash_callback;
     
     return self;
}

DS_Void BloomFilter_Destroy(BloomFilter self)
{
     Array_Destroy(self->array);
     free(self);
}

DS_Generic BloomFilter_Search(BloomFilter self, const DS_Generic data)
{
     DS_Size index;

     index = self->hash_callback.function(data, Array_GetSize(self->array), self->hash_callback.user_data);

     return Array_GetData(self->array, index);
}

DS_Void BloomFilter_Insert(BloomFilter self, const DS_Generic data)
{
     DS_Size index;

     index = self->hash_callback.function(data, Array_GetSize(self->array), self->hash_callback.user_data);

     Array_SetData(self->array, index, data);
}
