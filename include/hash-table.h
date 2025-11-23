#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <stddef.h>

typedef struct HashTable HashTable;
typedef struct HashTablePair HashTablePair;

typedef enum {
     HASH_TABLE_COMPARE_LESS = -1,
     HASH_TABLE_COMPARE_EQUAL = 0,
     HASH_TABLE_COMPARE_GREATER = 1
} HashTableCompare;

typedef struct {
     HashTableCompare (*function)(const void *data1, const void *data2, void *user_data);
     void *user_data;
} HashTableCompareCallback;

typedef struct {
     size_t (*function)(const void *data, size_t size, void *user_data);
     void *user_data;
} HashTableHashCallback;

__attribute__((visibility("default")))
HashTable *HashTable_Create(size_t key_size,
     size_t value_size,
     size_t bucket_count,
     HashTableHashCallback hash_callback,
     HashTableCompareCallback compare_callback);

__attribute__((visibility("default")))
void HashTable_Destroy(HashTable *this);

__attribute__((visibility("default")))
void *HashTable_GetKey(HashTablePair *pair);

__attribute__((visibility("default")))
void *HashTable_GetValue(HashTablePair *pair);

__attribute__((visibility("default")))
void HashTable_Insert(HashTable *this, const void *key, const void *value);

__attribute__((visibility("default")))
void HashTable_Remove(HashTable *this, const void *key);

__attribute__((visibility("default")))
HashTablePair *HashTable_Search(HashTable *this, const void *key);

#endif
