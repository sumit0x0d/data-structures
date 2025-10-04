#ifndef DATA_STRUCTURES_ARRAY_ITERATOR_H
#define DATA_STRUCTURES_ARRAY_ITERATOR_H

#include <array.h>

struct ArrayIterator {
     Array array;
     DS_Size index;
};

ArrayIterator ArrayIterator_Create(Array array);

#endif