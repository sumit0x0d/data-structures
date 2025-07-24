#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <hash-table.h>

static size_t _hash_int(const void *data, const size_t bucket_count, void *uData);
static int _compare_int(const void *data1, const void *data2,void *uData);

int
main()
{
     srand((int)time(NULL));
     struct hash_table *hash_table = HashTable_Create(sizeof (int), sizeof (int), 20, _hash_int, _compare_int, NULL);
     HashTable_Destroy(hash_table);
     return 0;
}

static size_t _hash_int(const void *data, const size_t bucket_count, void *uData)
{
     (void)uData;
     size_t index = *(int *)data * bucket_count;
     return index;
}

static int _compare_int(const void *data1, const void *data2, void *uData)
{
     (void)uData;
     int key1 = *(int *)data1;
     int key2 = *(int *)data2;
     if (key1 < key2) {
          return -1;
     }
     if (key1 > key2) {
          return 1;
     }
     return 0;
}
