#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <data-structures.h>

typedef struct HashTable * HashTable;
typedef struct HashTablePair * HashTablePair;

DATA_STRUCTURES_API
HashTable HashTable_Create(DS_Size key_size, DS_Size value_size, DS_Size bucket_count,
     DS_HashCallback hash_callback, DS_CompareCallback compare_callback);

DATA_STRUCTURES_API
DS_Void HashTable_Destroy(HashTable self);

DATA_STRUCTURES_API
DS_Generic HashTable_GetKey(HashTablePair pair);

DATA_STRUCTURES_API
DS_Generic HashTable_GetValue(HashTablePair pair);

DATA_STRUCTURES_API
DS_Void HashTable_Insert(HashTable self, const DS_Generic key, const DS_Generic value);

DATA_STRUCTURES_API
DS_Void HashTable_Remove(HashTable self, const DS_Generic key);

DATA_STRUCTURES_API
HashTablePair HashTable_Search(HashTable self, const DS_Generic key);

#endif
