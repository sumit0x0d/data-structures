#include <stdlib.h>

#include "hash-table-pair.h"

HashTablePair HashTablePair_Create(const DS_Data key, DS_Size sKey, const DS_Data value, DS_Size sValue)
{
    HashTablePair pair = (HashTablePair)malloc(sizeof (struct hash_table_pair));
    if (!pair) {
        return NULL;
    } 
    pair->key = malloc(sKey);
    if (!pair->key) {
        free(pair);
        return NULL;
    }
    pair->value = malloc(sValue);
    if (!pair->value) {
        free(pair->key);
        free(pair);
        return NULL;
    }
    memcpy(pair->key, key, sKey);
    memcpy(pair->value, value, sValue);
    pair->next = NULL;
    return pair;
}

void HashTablePair_Destroy(HashTablePair pair)
{
    free(pair->key);
    free(pair->value);
    free(pair);
}
