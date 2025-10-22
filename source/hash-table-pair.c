#include <stdlib.h>
#include <string.h>

#include "hash-table-pair.h"

HashTablePair HashTablePair_Create(const DS_Generic key, DS_Size key_size, const DS_Generic value, DS_Size value_size)
{
     HashTablePair self;
     
     self = (HashTablePair)malloc(sizeof (struct HashTablePair));
     if (!self) {
          return NULL;
     }

     self->key = malloc(key_size);
     if (!self->key) {
          free(self);
          return NULL;
     }

     self->value = malloc(value_size);
     if (!self->value) {
          free(self->key);
          free(self);
          return NULL;
     }

     memcpy(self->key, key, key_size);
     memcpy(self->value, value, value_size);
     self->next = NULL;

     return self;
}

DS_Void HashTablePair_Destroy(HashTablePair self)
{
     free(self->key);
     free(self->value);
     free(self);
}
