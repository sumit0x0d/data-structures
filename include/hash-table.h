#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct hash_table * HashTable;
typedef struct hash_table_pair * HashTablePair;

/**
 * Creates a new hash table.
 * @param sKey     Size of the key.
 * @param sValue   Size of the value.
 * @param nBucket  Number of buckets.
 * @param fHash    Function pointer for hashing keys.
 * @param fCompare Function pointer for comparing keys.
 * @param context  conext passed to hash and compare functions.
 * @return         HashTable.
 */
DS_API
HashTable HashTable_Create(DS_Size sKey, DS_Size sValue, DS_Size sBucket, DS_FunctionHash fHash,
                           DS_Context cHash, DS_FunctionCompare fCompare, DS_Context cCompare);

DS_API
DS_Void HashTable_Destroy(HashTable hTable);

DS_API
DS_Data HashTablePair_GetKey(HashTablePair htPair);

DS_API
DS_Data HashTablePair_GetValue(HashTablePair htPair);

DS_API
DS_Void HashTable_Insert(HashTable hTable, const DS_Data key, const DS_Data value);

DS_API
DS_Void HashTable_Remove(HashTable hTable, const DS_Data key);

DS_API
HashTablePair HashTable_Search(HashTable hTable, const DS_Data key);

#endif
