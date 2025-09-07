#include <stdlib.h>

#include "hash-table-pair.h"

typedef HashTablePair Pair;

Pair *HashTablePair_Create(const void *key, DS_Size sKey, const void *value, DS_Size sValue)
{
    Pair *pair = (Pair *)malloc(sizeof (Pair));
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

void HashTablePair_Destroy(Pair *pair)
{
    free(pair->key);
    free(pair->value);
    free(pair);
}
