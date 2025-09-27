#ifndef DATA_STRUCTURES_HASH_TABLE_PAIR_H
#define DATA_STRUCTURES_HASH_TABLE_PAIR_H

#include <hash-table.h>

struct hash_table_pair {
    DS_Data key;
    DS_Data value;
    HashTablePair next;
};

HashTablePair HashTablePair_Create(const DS_Data key, DS_Size key_size, const DS_Data value, DS_Size value_size);

DS_Void HashTablePair_Destroy(HashTablePair pair);

#endif