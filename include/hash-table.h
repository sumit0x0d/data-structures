#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct hash_table HashTable;
typedef struct hash_table_pair HashTablePair;

typedef size_t (*HashTableHash)(const void *key, size_t bCount, void *uData);
typedef int (*HashTableCompare)(const void *key1, const void *key2, void *uData);

HashTable *HashTable_Create(size_t kSize, size_t vSize, size_t bCount, HashTableHash htHash, HashTableCompare htCompare, void *uData);
void HashTable_Destroy(HashTable *hTable);

void *HashTablePair_GetKey(HashTablePair *htPair);
void *HashTablePair_GetValue(HashTablePair *htPair);

void HashTable_Insert(HashTable *hTable, const void *key, const void *value);
void HashTable_Remove(HashTable *hTable, const void *key);
HashTablePair *HashTable_Search(HashTable *hTable, const void *key);

#endif
