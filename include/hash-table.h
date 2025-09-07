#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct hash_table HashTable;
typedef struct hash_table_pair HashTablePair;

/**
 * Creates a new hash table.
 * @param sKey     Size of the key in bytes.
 * @param sValue   Size of the value in bytes.
 * @param nBucket  Number of buckets in the hash table.
 * @param fHash    Function pointer for hashing keys.
 * @param fCompare Function pointer for comparing keys.
 * @param dUser    User data passed to hash and compare functions.
 * @return         Pointer to the created HashTable.
 */
DS_PUBLIC_API
HashTable *HashTable_Create(DS_Size sKey, DS_Size sValue, DS_Size nBucket, DS_FunctionHash fHash,
                               DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void HashTable_Destroy(HashTable *hTable);

DS_PUBLIC_API
DS_Data HashTablePair_GetKey(HashTablePair *htPair);

DS_PUBLIC_API
DS_Data HashTablePair_GetValue(HashTablePair *htPair);

DS_PUBLIC_API
void HashTable_Insert(HashTable *hTable, const DS_Data key, const DS_Data value);

DS_PUBLIC_API
void HashTable_Remove(HashTable *hTable, const DS_Data key);

DS_PUBLIC_API
HashTablePair *HashTable_Search(HashTable *hTable, const DS_Data key);

#endif
