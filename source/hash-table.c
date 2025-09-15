#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include <hash-table-pair.h>

struct hash_table {
     Pair *pair;
     DS_Size key_size;
     DS_Size value_size;
     DS_Size bucket_count;
     DS_FunctionHash hash_function;
     DS_Context hash_context;
     DS_FunctionCompare compare_function;
     DS_Context compare_context;
};

HashTable HashTable_Create(DS_Size sKey, DS_Size sValue, DS_Size nBucket, DS_FunctionHash fHash,
                           DS_Context cHash, DS_FunctionCompare fCompare, DS_Context cCompare)
{
     HashTable hTable = (HashTable)malloc(sizeof (struct hash_table));
     if (!hTable) {
          return NULL;
     }
     hTable->pair = (HashTablePair)calloc(nBucket, sizeof (struct hash_table_pair));
     if (!hTable->pair) {
          free(hTable);
          return NULL;
     }
     hTable->key_size = sKey;
     hTable->value_size = sValue;
     hTable->bucket_count = nBucket;
     hTable->hash_function = fHash;
     hTable->compare_context = cHash;
     hTable->compare_function = fCompare;
     hTable->compare_context = cCompare;
     return hTable;
}

DS_Void HashTable_Destroy(HashTable hTable)
{
     for (DS_Size i = 0; i < hTable->bucket_count; i++) {
          if (hTable->pair[i]) {
               HashTablePair_Destroy(hTable->pair[i]);
          }
     }
     free(hTable);
}

DS_Void *HashTablePair_GetKey(HashTablePair pair)
{
     return pair->key;
}

DS_Void *HashTablePair_GetValue(HashTablePair pair)
{
     return pair->value;
}

DS_Void HashTable_Insert(HashTable hTable, const DS_Void *key, const DS_Void *value)
{
     DS_Size index = hTable->hash_function(key, hTable->bucket_count, hTable->hash_context);
     if (!hTable->pair[index]) {
          hTable->pair[index] = HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
          return;
     }
     DS_Compare compare = DS_COMPARE_EQUAL;
     HashTablePair pair = hTable->pair[index];
     do {
          compare = hTable->compare_function(key, pair->key, hTable->compare_context);
          if (compare) {
               pair = pair->next;
          } else {
               memcpy(hTable->pair[index]->value, value, hTable->value_size);
               return;
          } 
     } while (compare && pair->next);
     pair->next = HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
}

DS_Void HashTable_Remove(HashTable hTable, const DS_Void *key)
{
     DS_Size index = hTable->hash_function(key, hTable->bucket_count, hTable->hash_context);
     if (hTable->pair[index]) {
          int compare = 0;
          HashTablePair pair = hTable->pair[index];
          HashTablePair ppair = pair;
          do {
               compare = hTable->compare_function(key, pair->key, hTable->compare_context);
               if (compare) {
                    ppair = pair;
                    pair = pair->next;
               } else {
                    ppair->next = pair->next;
                    HashTablePair_Destroy(pair->next);
                    pair = NULL;
               }
          } while (compare && pair->next);
     };
}

HashTablePair HashTable_Search(HashTable hTable, const DS_Void *key)
{
     DS_Size index = hTable->hash_function(key, hTable->bucket_count, hTable->hash_context);
     if (hTable->pair[index]) {
          DS_Compare compare = 0;
          HashTablePair pair = hTable->pair[index];
          do {
               compare = hTable->compare_function(key, pair->key, hTable->compare_context);
               if (compare) {
                    pair = pair->next;
               } else {
                    return pair;
               }
          } while (compare != DS_COMPARE_EQUAL && pair);
     }
     return NULL;
}
