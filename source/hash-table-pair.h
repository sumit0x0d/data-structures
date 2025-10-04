#ifndef DATA_STRUCTURES_HASH_TABLE_PAIR_H
#define DATA_STRUCTURES_HASH_TABLE_PAIR_H

#include <hash-table.h>

struct HashTablePair {
     DS_Generic key;
     DS_Generic value;
     HashTablePair next;
};

HashTablePair HashTablePair_Create(const DS_Generic key, DS_Size key_size,
                                   const DS_Generic value, DS_Size value_size);

DS_Void HashTablePair_Destroy(HashTablePair pair);

#endif