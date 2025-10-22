#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include "hash-table-pair.h"

struct HashTable {
     HashTablePair *pair;
     DS_Size key_size;
     DS_Size value_size;
     DS_Size bucket_count;
     DS_HashCallback hash_callback;
     DS_CompareCallback compare_callback;
};

HashTable HashTable_Create(DS_Size key_size, DS_Size value_size, DS_Size bucket_count,
     DS_HashCallback hash_callback, DS_CompareCallback compare_callback)
{
     HashTable self;
     
     self = (HashTable)malloc(sizeof (struct HashTable));
     if (!self) {
          return NULL;
     }
     
     self->pair = (HashTablePair *)calloc(bucket_count, sizeof (struct HashTablePair));
     if (!self->pair) {
          free(self);
          return NULL;
     }
     
     self->key_size = key_size;
     self->value_size = value_size;
     self->bucket_count = bucket_count;
     self->hash_callback.function = hash_callback.function;
     self->hash_callback.context = hash_callback.context;
     self->compare_callback.function = compare_callback.function;
     self->compare_callback.context = compare_callback.context;
     
     return self;
}

DS_Void HashTable_Destroy(HashTable self)
{
     DS_Size i;
     
     for (i = 0; i < self->bucket_count; i++) {
          if (self->pair[i]) {
               HashTablePair_Destroy(self->pair[i]);
          }
     }
     
     free(self);
}

DS_Generic HashTable_GetKey(HashTablePair pair)
{
     return pair->key;
}

DS_Generic HashTable_GetValue(HashTablePair pair)
{
     return pair->value;
}

DS_Void HashTable_Insert(HashTable self, const DS_Generic key, const DS_Generic value)
{
     DS_Size index;
     DS_Compare compare;
     HashTablePair pair;
     
     index = self->hash_callback.function(key, self->bucket_count, self->hash_callback.context);
     
     if (!self->pair[index]) {
          self->pair[index] = HashTablePair_Create(key, self->key_size, value, self->value_size);
          return;
     }

     pair = self->pair[index];

     do {
          compare = self->compare_callback.function(key, pair->key, self->compare_callback.context);
          if (compare) {
               pair = pair->next;
          } else {
               memcpy(pair->value, value, self->value_size);
               return;
          } 
     } while (compare && pair->next);

     pair->next = HashTablePair_Create(key, self->key_size, value, self->value_size);
}

DS_Void HashTable_Remove(HashTable self, const DS_Generic key)
{
     DS_Size index;
     HashTablePair pair;
     HashTablePair previous;
     DS_Compare compare;

     index = self->hash_callback.function(key, self->bucket_count, self->hash_callback.context);
     
     if (!self->pair[index]) {
          return;
     };

     pair = self->pair[index];
     previous = pair;

     do {
          compare = self->compare_callback.function(key, pair->key, self->compare_callback.context);
          switch (compare) {
          case DS_COMPARE_EQUAL:
               previous->next = pair->next;
               HashTablePair_Destroy(pair->next);
               pair = NULL;
               break;
          case DS_COMPARE_LESS:
          case DS_COMPARE_GREATER:
               previous = pair;
               pair = pair->next;
               break;
          }
     } while (compare && pair->next);
}

HashTablePair HashTable_Search(HashTable self, const DS_Generic key)
{
     DS_Size index;
     HashTablePair pair;
     DS_Compare compare;
     
     index = self->hash_callback.function(key, self->bucket_count, self->hash_callback.context);

     if (!self->pair[index]) {
          return NULL;
     }

     pair = self->pair[index];

     do {
          compare = self->compare_callback.function(key, pair->key, self->compare_callback.context);
          switch (compare) {
          case DS_COMPARE_EQUAL:
               return pair;
          case DS_COMPARE_LESS:
          case DS_COMPARE_GREATER:
               pair = pair->next;
               break;
          }
     } while (pair);

     return NULL;
}
