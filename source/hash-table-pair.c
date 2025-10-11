#include <stdlib.h>
#include <string.h>

#include "hash-table-pair.h"

HashTablePair HashTablePair_Create(
     const DS_Generic key,
     DS_Size          key_size,
     const DS_Generic value,
     DS_Size          value_size
) {
     HashTablePair pair;
     
     pair = (HashTablePair)malloc(sizeof (struct HashTablePair));
     if (!pair) {
          return NULL;
     }

     pair->key = malloc(key_size);
     if (!pair->key) {
          free(pair);
          return NULL;
     }

     pair->value = malloc(value_size);
     if (!pair->value) {
          free(pair->key);
          free(pair);
          return NULL;
     }

     memcpy(pair->key, key, key_size);
     memcpy(pair->value, value, value_size);
     pair->next = NULL;

     return pair;
}

DS_Void HashTablePair_Destroy(
     HashTablePair pair
) {
     free(pair->key);
     free(pair->value);
     free(pair);
}
