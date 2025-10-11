#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include "hash-table-pair.h"

struct HashTable {
     HashTablePair      *pair;
     DS_Size            key_size;
     DS_Size            value_size;
     DS_Size            bucket_count;
     DS_CallbackHash    hash_callback;
     DS_Generic         hash_context;
     DS_CallbackCompare compare_callback;
     DS_Generic         compare_context;
};

HashTable HashTable_Create(
     DS_Size            key_size,
     DS_Size            value_size,
     DS_Size            bucket_count,
     DS_CallbackHash    hash_callback,
     DS_Generic         hash_context,
     DS_CallbackCompare compare_callback,
     DS_Generic         compare_context
) {
     HashTable hash_table;
     
     hash_table = (HashTable)malloc(sizeof (struct HashTable));
     if (!hash_table) {
          return NULL;
     }
     
     hash_table->pair = (HashTablePair *)calloc(
          bucket_count, sizeof (struct HashTablePair));
     if (!hash_table->pair) {
          free(hash_table);
          return NULL;
     }
     
     hash_table->key_size = key_size;
     hash_table->value_size = value_size;
     hash_table->bucket_count = bucket_count;
     hash_table->hash_callback = hash_callback;
     hash_table->hash_context = hash_context;
     hash_table->compare_callback = compare_callback;
     hash_table->compare_context = compare_context;
     
     return hash_table;
}

DS_Void HashTable_Destroy(
     HashTable hash_table
) {
     DS_Size i;
     
     for (i = 0; i < hash_table->bucket_count; i++) {
          if (hash_table->pair[i]) {
               HashTablePair_Destroy(hash_table->pair[i]);
          }
     }
     
     free(hash_table);
}

DS_Generic HashTable_GetKey(
     HashTablePair pair
) {
     return pair->key;
}

DS_Generic HashTable_GetValue(
     HashTablePair pair
) {
     return pair->value;
}

DS_Void HashTable_Insert(
     HashTable        hash_table,
     const DS_Generic key,
     const DS_Generic value
) {
     DS_Size       index;
     DS_Compare    compare;
     HashTablePair pair;
     
     index = hash_table->hash_callback(key,
          hash_table->bucket_count, hash_table->hash_context);
     
     if (!hash_table->pair[index]) {
          hash_table->pair[index] = HashTablePair_Create(key,
               hash_table->key_size, value, hash_table->value_size);
          return;
     }

     pair = hash_table->pair[index];

     do {
          compare = hash_table->compare_callback(key,
               pair->key, hash_table->compare_context);
          if (compare) {
               pair = pair->next;
          } else {
               memcpy(hash_table->pair[index]->value, value, hash_table->value_size);
               return;
          } 
     } while (compare && pair->next);

     pair->next = HashTablePair_Create(key,
          hash_table->key_size, value, hash_table->value_size);
}

DS_Void HashTable_Remove(
     HashTable        hash_table,
     const DS_Generic key
) {
     DS_Size       index;
     HashTablePair pair;
     HashTablePair previous;
     DS_Compare    compare;

     index = hash_table->hash_callback(key,
          hash_table->bucket_count, hash_table->hash_context);
     
     if (!hash_table->pair[index]) {
          return;
     };

     pair = hash_table->pair[index];
     previous = pair;

     do {
          compare = hash_table->compare_callback(key,
               pair->key, hash_table->compare_context);
          if (compare) {
               previous = pair;
               pair = pair->next;
          } else {
               previous->next = pair->next;
               HashTablePair_Destroy(pair->next);
               pair = NULL;
          }
     } while (compare && pair->next);
}

HashTablePair HashTable_Search(
     HashTable        hash_table,
     const DS_Generic key
) {
     DS_Size       index;
     HashTablePair pair;
     DS_Compare    compare;
     
     index = hash_table->hash_callback(key,
          hash_table->bucket_count, hash_table->hash_context);
     
     if (!hash_table->pair[index]) {
          return NULL;
     }
     
     pair = hash_table->pair[index];
     
     do {
          compare = hash_table->compare_callback(key,
               pair->key, hash_table->compare_context);
          if (compare) {
               pair = pair->next;
          } else {
               return pair;
          }
     } while (compare != DS_COMPARE_EQUAL && pair);

     return NULL;
}
