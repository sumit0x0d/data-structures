#include <stdlib.h>

#include <array-iterator.h>

ArrayIterator ArrayIterator_Create(Array array)
{
     ArrayIterator iterator;
     
     iterator = (ArrayIterator)malloc(sizeof (struct ArrayIterator));
     if (!iterator) {
          return NULL;
     }

     iterator->array = array;
     iterator->index = 0;

     return iterator;
}