#ifndef DATA_STRUCTURES_BLOOM_FILTER_H
#define DATA_STRUCTURES_BLOOM_FILTER_H

typedef struct BloomFilter BloomFilter;

typedef struct {
     size_t (*function)(const void *data, size_t size, void *user_data);
     void *user_data;
} BloomFilterHashCallback;

__attribute__((visibility("default")))
BloomFilter *BloomFilter_Create(size_t data_size, size_t bucket_count, BloomFilterHashCallback hash_callback);

__attribute__((visibility("default")))
void BloomFilter_Destroy(BloomFilter *this);

__attribute__((visibility("default")))
void *BloomFilter_Search(BloomFilter *this, const void *data);

__attribute__((visibility("default")))
void BloomFilter_Insert(BloomFilter *this, const void *data);

#endif
