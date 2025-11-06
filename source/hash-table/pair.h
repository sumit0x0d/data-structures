#ifndef DATA_STRUCTURES_HASH_TABLE_PAIR_H
#define DATA_STRUCTURES_HASH_TABLE_PAIR_H

#include <hash-table.h>

struct HashTablePair {
     void *key;
     void *value;
     HashTablePair next;
};

HashTablePair *HashTablePair_Create(const void *key, size_t key_size, const void *value, size_t value_size);
void HashTablePair_Destroy(HashTablePair *this);

#endif