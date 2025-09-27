#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct hash_table * HashTable;
typedef struct hash_table_pair * HashTablePair;

DS_API
HashTable HashTable_Create(DS_Size key_size, DS_Size value_size, DS_Size bucket_count, DS_FunctionHash hash_function,
                           DS_Context hash_context, DS_FunctionCompare compare_function, DS_Context compare_context);

DS_API
DS_Void HashTable_Destroy(HashTable table);

DS_API
DS_Data HashTable_GetKey(HashTablePair pair);

DS_API
DS_Data HashTable_GetValue(HashTablePair pair);

DS_API
DS_Void HashTable_Insert(HashTable table, const DS_Data key, const DS_Data value);

DS_API
DS_Void HashTable_Remove(HashTable table, const DS_Data key);

DS_API
HashTablePair HashTable_Search(HashTable table, const DS_Data key);

#endif
