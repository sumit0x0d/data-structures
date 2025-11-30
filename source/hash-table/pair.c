#include <stdlib.h>
#include <string.h>

#include "pair.h"

HashTablePair *HashTablePair_Create(const void *key, size_t key_size, const void *value, size_t value_size)
{
     HashTablePair *this;

     this = (HashTablePair *)malloc(sizeof (HashTablePair));
     if (!this) {
          return NULL;
     }

     this->key = malloc(key_size);
     if (!this->key) {
          free(this);
          return NULL;
     }

     this->value = malloc(value_size);
     if (!this->value) {
          free(this->key);
          free(this);
          return NULL;
     }

     memcpy(this->key, key, key_size);
     memcpy(this->value, value, value_size);
     this->next = NULL;

     return this;
}

void HashTablePair_Destroy(HashTablePair *this)
{
     free(this->key);
     free(this->value);
     free(this);
}
