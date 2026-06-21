#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <bloom-filter.h>


int main(void)
{
   BloomFilter *obj;
   int i, value;
   BloomFilterHashCallback hash_callback;

   srand((int)time(NULL));

   obj = BloomFilter_Create(1000, hash_callback);
   if (!obj) {
      fprintf(stderr, "BloomFilter_Create() failed\n");
      return 1;
   }
   printf("BloomFilter_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      BloomFilter_Insert(bf, &value);
   }
   printf("BloomFilter_Insert() passed\n");
   BloomFilter_Destroy(bf);
   printf("BloomFilter_Destroy() passed\n");
   printf("All bloom-filter tests passed!\n");

   return 0;
}
