#include <stdlib.h>
#include <string.h>

#include <bloom-filter.h>

struct BloomFilter {
     void *base;
     size_t data_size;
     size_t capacity;
     BloomFilterHashCallback hash_callback;
};

BloomFilter *BloomFilter_Create(size_t data_size, size_t capacity, BloomFilterHashCallback hash_callback)
{
     BloomFilter *this;

     this = (BloomFilter *)malloc(sizeof (BloomFilter));
     if (!this) {
          return NULL;
     }

     this->base = malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->hash_callback = hash_callback;

     return this;
}

void BloomFilter_Destroy(BloomFilter *this)
{
     free(this->base);
     free(this);
}

void *BloomFilter_Search(BloomFilter *this, const void *data)
{
     size_t index;

     index = this->hash_callback.function(data, this->capacity, this->hash_callback.user_data);

     return (char *)this->base + (this->data_size * index);
}

void BloomFilter_Insert(BloomFilter *this, const void *data)
{
     size_t index;

     index = this->hash_callback.function(data, this->capacity, this->hash_callback.user_data);
     memcpy((char *)this->base + (this->data_size * index), data, this->data_size);
}
