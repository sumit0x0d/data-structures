#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <hash-table.h>

static HashTableCompare HashTable_CompareInt(const void *data1,
   const void *data2, void *user_data);
static size_t HashTable_HashInt(const void *data, size_t size, void *user_data);

int main(void)
{
   HashTable *hash_table;
   int i, value;
   HashTableHashCallback hash_callback;
   HashTableCompareCallback compare_callback;
   HashTablePair *pair;

   srand((int)time(NULL));

   hash_callback.function = HashTable_HashInt;
   hash_callback.user_data = NULL;
   compare_callback.function = HashTable_CompareInt;
   compare_callback.user_data = NULL;

   hash_table = HashTable_Create(sizeof(int), sizeof(int), 100,
      hash_callback, compare_callback);
   if (!hash_table) {
      fprintf(stderr, "HashTable_Create() failed\n");
      return 1;
   }
   printf("HashTable_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      HashTable_Insert(hash_table, &value, &value);
   }
   printf("HashTable_Insert() passed\n");

   value = rand() % 100;
   HashTable_Insert(hash_table, &value, &value);
   pair = HashTable_Search(hash_table, &value);
   if (!pair) {
      fprintf(stderr, "HashTable_Search() failed\n");
      HashTable_Destroy(hash_table);
      return 1;
   }
   if (*(int *)HashTable_GetValue(pair) != value) {
      fprintf(stderr, "HashTable_Search() returned wrong value\n");
      HashTable_Destroy(hash_table);
      return 1;
   }
   printf("HashTable_Search() passed\n");

   HashTable_Destroy(hash_table);
   printf("HashTable_Destroy() passed\n");
   printf("All hash-table tests passed!\n");

   return 0;
}

static HashTableCompare HashTable_CompareInt(const void *data1,
   const void *data2, void *user_data)
{
   (void)user_data;
   if (*(int *)data1 < *(int *)data2) {
      return HASH_TABLE_COMPARE_LESS;
   }
   if (*(int *)data1 > *(int *)data2) {
      return HASH_TABLE_COMPARE_GREATER;
   }
   return HASH_TABLE_COMPARE_EQUAL;
}

static size_t HashTable_HashInt(const void *data, size_t size, void *user_data)
{
   (void)user_data;
   return (*(int *)data) % size;
}
