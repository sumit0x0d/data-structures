#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bloom-filter.h"

static size_t _hash_int(const void *data, size_t bCount);

int main()
{
     srand((int)time(NULL));
     BloomFilter *bFilter = BloomFilter_Create(sizeof (int), 20, _hash_int);
     int a = 0;
     printf("%d\n", BloomFilter_Search(bFilter, &a));
     return 0;
}

static size_t _hash_int(const void *data, size_t bCount)
{
     size_t index = *(int *)data * bCount;
     return index;
}

