#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <bloom-filter.h>

static size_t _HashInt(const void *data, size_t size, void *user_data);

int main(void)
{
   BloomFilter *bloom_filter;
   int i, value;
   BloomFilterHashCallback hash_callback;
   void *result;

   srand((int)time(NULL));

   hash_callback.function = _HashInt;
   hash_callback.user_data = NULL;

   bloom_filter = BloomFilter_Create(sizeof(int), 1000, hash_callback);
   if (!bloom_filter) {
      fprintf(stderr, "BloomFilter_Create() failed\n");
      return 1;
   }
   printf("BloomFilter_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      BloomFilter_Insert(bloom_filter, &value);
   }
   printf("BloomFilter_Insert() passed\n");

   value = rand() % 100;
   BloomFilter_Insert(bloom_filter, &value);
   result = BloomFilter_Search(bloom_filter, &value);
   if (!result) {
      fprintf(stderr, "BloomFilter_Search() failed\n");
      BloomFilter_Destroy(bloom_filter);
      return 1;
   }
   printf("BloomFilter_Search() passed\n");

   BloomFilter_Destroy(bloom_filter);
   printf("BloomFilter_Destroy() passed\n");
   printf("All bloom-filter tests passed!\n");

   return 0;
}

static size_t _HashInt(const void *data, size_t size, void *user_data)
{
   (void)user_data;
   return (*(int *)data) % size;
}
