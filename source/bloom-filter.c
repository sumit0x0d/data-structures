#include <assert.h>
#include <stdlib.h>

#include <bloom-filter.h>

struct BloomFilter {
     DS_Generic base;
     DS_Size data_size;
     DS_Size capacity;
     DS_HashCallback hash_callback;
};

BloomFilter BloomFilter_Create(DS_Size data_size, DS_Size capacity, DS_HashCallback hash_callback)
{
     BloomFilter this;

     this = (BloomFilter)malloc(sizeof (struct BloomFilter));
     if (!this) {
          return NULL;
     }
     
     this->base = (DS_Generic)malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };
     
     this->hash_callback = hash_callback;
     
     return this;
}

DS_Void BloomFilter_Destroy(BloomFilter this)
{
     free(this->base);
     free(this);
}

DS_Generic BloomFilter_Search(BloomFilter this, const DS_Generic data)
{
     DS_Size index;

     index = this->hash_callback.function(data, this->capacity, this->hash_callback.user_data);

     return (DS_Int8 *)this->base + (this->data_size * index);
}

DS_Void BloomFilter_Insert(BloomFilter this, const DS_Generic data)
{
     DS_Size index;

     index = this->hash_callback.function(data, this->capacity, this->hash_callback.user_data);
     memcpy((DS_Int8 *)this->base + (this->data_size * index), data, this->data_size);
}
