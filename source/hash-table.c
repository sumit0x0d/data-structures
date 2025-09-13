#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include <hash-table-pair.h>

typedef HashTablePair Pair;

struct hash_table {
     Pair **pair;
     DS_Size key_size;
     DS_Size value_size;
     DS_Size bucket_count;
     DS_FunctionHash hash;
     DS_FunctionCompare compare;
     void *user_data;
};

HashTable *HashTable_Create(DS_Size sKey, DS_Size sValue, DS_Size bCount, DS_FunctionHash hash, DS_FunctionCompare compare, DS_Context context)
{
     HashTable *hTable = (HashTable *)malloc(sizeof (HashTable));
     if (!hTable) {
          return NULL;
     }
     hTable->pair = (Pair **)calloc(bCount, sizeof (struct Pair *));
     if (!hTable->pair) {
          free(hTable);
          return NULL;
     }
     hTable->key_size = sKey;
     hTable->value_size = sValue;
     hTable->bucket_count = bCount;
     hTable->hash = hash;
     hTable->compare = compare;
     hTable->user_data = uData;
     return hTable;
}

void HashTable_Destroy(HashTable *hTable)
{
     for (DS_Size i = 0; i < hTable->bucket_count; i++) {
          if (hTable->pair[i]) {
               HashTablePair_Destroy(hTable->pair[i]);
          }
     }
     free(hTable);
}

void *HashTablePair_GetKey(Pair *pair)
{
     return pair->key;
}

void *HashTablePair_GetValue(Pair *pair)
{
     return pair->value;
}

void HashTable_Insert(HashTable *hTable, const void *key, const void *value)
{
     DS_Size index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
     if (!hTable->pair[index]) {
          hTable->pair[index] = HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
          return;
     }
     int compare = 0;
     Pair *pair = hTable->pair[index];
     do {
          compare = hTable->compare(key, pair->key, hTable->user_data);
          if (compare) {
               pair = pair->next;
          } else {
               memcpy(hTable->pair[index]->value, value, hTable->value_size);
               return;
          } 
     } while (compare && pair->next);
     pair->next = HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
}

void HashTable_Remove(HashTable *hTable, const void *key)
{
     DS_Size index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
     if (hTable->pair[index]) {
          int compare = 0;
          Pair *pair = hTable->pair[index];
          Pair *ppair = pair;
          do {
               compare = hTable->compare(key, pair->key, hTable->user_data);
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

Pair *HashTable_Search(HashTable *hTable, const void *key)
{
     DS_Size index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
     if (hTable->pair[index]) {
          int compare = 0;
          Pair *pair = hTable->pair[index];
          do {
               compare = hTable->compare(key, pair->key, hTable->user_data);
               if (compare) {
                    pair = pair->next;
               } else {
                    return pair;
               }
          } while (compare && pair);
     }
     return NULL;
}
