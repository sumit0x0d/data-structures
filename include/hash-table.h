#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct hash_table * HashTable;
typedef struct hash_table_pair * HashTablePair;

DS_API
HashTable HashTable_Create(DS_Size key_size, DS_Size value_size, DS_Size bucket_count, DS_CallbackHash hash_callback,
                           DS_Generic hash_context, DS_CallbackCompare compare_callback, DS_Generic compare_context);

DS_API
DS_Void HashTable_Destroy(HashTable table);

DS_API
DS_Generic HashTable_GetKey(HashTablePair pair);

DS_API
DS_Generic HashTable_GetValue(HashTablePair pair);

DS_API
DS_Void HashTable_Insert(HashTable table, const DS_Generic key, const DS_Generic value);

DS_API
DS_Void HashTable_Remove(HashTable table, const DS_Generic key);

DS_API
HashTablePair HashTable_Search(HashTable table, const DS_Generic key);

#endif
