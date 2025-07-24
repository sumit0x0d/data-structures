#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

typedef HashTablePair Pair;
typedef HashTableHash Hash;
typedef HashTableCompare Compare;

struct hash_table_pair {
     void *key;
     void *value;
     Pair *next;
};

struct hash_table {
     Pair **pair;
     size_t key_size;
     size_t value_size;
     size_t bucket_count;
     Hash hash;
     Compare compare;
     void *user_data;
};

static Pair *_HashTablePair_Create(const void *key, size_t kSize, const void *value, size_t vSize);
static void _HashTablePair_Destroy(Pair *pair);

HashTable *HashTable_Create(size_t kSize, size_t vSize, size_t bCount, Hash hash, Compare compare, void *uData)
{
     HashTable *hTable = (HashTable *)malloc(sizeof (HashTable));
     assert(hTable);
     hTable->pair = (Pair **)calloc(bCount, sizeof (struct Pair *));
     assert(hash_table->pair);
     hTable->key_size = kSize;
     hTable->value_size = vSize;
     hTable->bucket_count = bCount;
     hTable->hash = hash;
     hTable->compare = compare;
     hTable->user_data = uData;
     return hTable;
}

void HashTable_Destroy(HashTable *hTable)
{
     for (size_t i = 0; i < hTable->bucket_count; i++) {
          if (hTable->pair[i]) {
               _HashTablePair_Destroy(hTable->pair[i]);
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
     size_t index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
     if (!hTable->pair[index]) {
          hTable->pair[index] = _HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
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
     pair->next = _HashTablePair_Create(key, hTable->key_size, value, hTable->value_size);
}

void HashTable_Remove(HashTable *hTable, const void *key)
{
     size_t index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
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
                    _HashTablePair_Destroy(pair->next);
                    pair = NULL;
               }
          } while (compare && pair->next);
     };
}

Pair *HashTable_Search(HashTable *hTable, const void *key)
{
     size_t index = hTable->hash(key, hTable->bucket_count, hTable->user_data);
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

static Pair *_HashTablePair_Create(const void *key, size_t kSize, const void *value, size_t vSize)
{
     Pair *pair = (Pair *)malloc(sizeof (Pair));
     assert(pair); 
     pair->key = malloc(kSize);
     assert(pair->key);
     pair->value = malloc(vSize);
     assert(pair->value);
     memcpy(pair->key, key, kSize);
     memcpy(pair->value, value, vSize);
     pair->next = NULL;
     return pair;
}

static void _HashTablePair_Destroy(Pair *pair)
{
     free(pair->key);
     free(pair->value);
     free(pair);
}
