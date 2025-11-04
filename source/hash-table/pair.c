#include <stdlib.h>
#include <string.h>

#include "pair.h"

HashTablePair HashTablePair_Create(const DS_Generic key, DS_Size key_size, const DS_Generic value, DS_Size value_size)
{
     HashTablePair this;
     
     this = (HashTablePair)malloc(sizeof (struct HashTablePair));
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

DS_Void HashTablePair_Destroy(HashTablePair this)
{
     free(this->key);
     free(this->value);
     free(this);
}
