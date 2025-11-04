#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include "hash-table/pair.h"

struct HashTable {
     HashTablePair *pair;
     size_t key_size;
     size_t value_size;
     size_t bucket_count;
     HashTableHashCallback hash_callback;
     HashTableCompareCallback compare_callback;
};

HashTable HashTable_Create(size_t key_size, size_t value_size, size_t bucket_count,
     HashTableHashCallback hash_callback, HashTableCompareCallback compare_callback)
{
     HashTable this;

     this = (HashTable)malloc(sizeof (struct HashTable));
     if (!this) {
          return NULL;
     }

     this->pair = (HashTablePair *)calloc(bucket_count, sizeof (struct HashTablePair));
     if (!this->pair) {
          free(this);
          return NULL;
     }

     this->key_size = key_size;
     this->value_size = value_size;
     this->bucket_count = bucket_count;
     this->hash_callback = hash_callback;
     this->compare_callback = compare_callback;

     return this;
}

void HashTable_Destroy(HashTable this)
{
     size_t i;

     for (i = 0; i < this->bucket_count; i++) {
          if (this->pair[i]) {
               HashTablePair_Destroy(this->pair[i]);
          }
     }

     free(this);
}

void *HashTable_GetKey(HashTablePair pair)
{
     return pair->key;
}

void *HashTable_GetValue(HashTablePair pair)
{
     return pair->value;
}

void HashTable_Insert(HashTable this, const void *key, const void *value)
{
     size_t index;
     HashTableCompare compare;
     HashTablePair pair;

     index = this->hash_callback.function(key, this->bucket_count, this->hash_callback.user_data);

     if (!this->pair[index]) {
          this->pair[index] = HashTablePair_Create(key, this->key_size, value, this->value_size);
          return;
     }

     pair = this->pair[index];

     do {
          compare = this->compare_callback.function(key, pair->key, this->compare_callback.user_data);
          if (compare) {
               pair = pair->next;
          } else {
               memcpy(pair->value, value, this->value_size);
               return;
          } 
     } while (compare && pair->next);

     pair->next = HashTablePair_Create(key, this->key_size, value, this->value_size);
}

void HashTable_Remove(HashTable this, const void *key)
{
     size_t index;
     HashTablePair pair;
     HashTablePair previous;
     HashTableCompare compare;

     index = this->hash_callback.function(key, this->bucket_count, this->hash_callback.user_data);

     if (!this->pair[index]) {
          return;
     };

     pair = this->pair[index];
     previous = pair;

     do {
          compare = this->compare_callback.function(key, pair->key, this->compare_callback.user_data);
          switch (compare) {
          case HASH_TABLE_COMPARE_EQUAL:
               previous->next = pair->next;
               HashTablePair_Destroy(pair->next);
               pair = NULL;
               break;
          case HASH_TABLE_COMPARE_LESS:
          case HASH_TABLE_COMPARE_GREATER:
               previous = pair;
               pair = pair->next;
               break;
          }
     } while (compare && pair->next);
}

HashTablePair HashTable_Search(HashTable this, const void *key)
{
     size_t index;
     HashTablePair pair;
     HashTableCompare compare;

     index = this->hash_callback.function(key, this->bucket_count, this->hash_callback.user_data);

     if (!this->pair[index]) {
          return NULL;
     }

     pair = this->pair[index];
     do {
          compare = this->compare_callback.function(key, pair->key, this->compare_callback.user_data);
          switch (compare) {
          case HASH_TABLE_COMPARE_EQUAL:
               return pair;
          case HASH_TABLE_COMPARE_LESS:
          case HASH_TABLE_COMPARE_GREATER:
               pair = pair->next;
               break;
          }
     } while (pair);

     return NULL;
}
