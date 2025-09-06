#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct hash_table HashTable;
typedef struct hash_table_pair HashTablePair;

DS_PUBLIC_API
HashTable *DS_HashTable_Create(DS_Size sKey, DS_Size sValue, DS_Size bCount, DS_FunctionHash fHash,
                               DS_FunctionCompare fCompare, DS_Data dUser);

DS_PUBLIC_API
void DS_HashTable_Destroy(HashTable *hTable);

DS_PUBLIC_API
DS_Data DS_HashTablePair_GetKey(HashTablePair *htPair);

DS_PUBLIC_API
DS_Data DS_HashTablePair_GetValue(HashTablePair *htPair);

DS_PUBLIC_API
void DS_HashTable_Insert(HashTable *hTable, const DS_Data key, const DS_Data value);

DS_PUBLIC_API
void DS_HashTable_Remove(HashTable *hTable, const DS_Data key);

DS_PUBLIC_API
HashTablePair *DS_HashTable_Search(HashTable *hTable, const DS_Data key);

#endif
