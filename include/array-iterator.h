#ifndef DATA_STRUCTURES_ARRAY_ITERATOR_H
#define DATA_STRUCTURES_ARRAY_ITERATOR_H

#include <array.h>

typedef enum {
     ARRAY_ITERATOR_OK,
     ARRAY_ITERATOR_END,
     ARRAY_ITERATOR_ERROR
} ArrayIteratorStatus;

struct ArrayIterator {
     Array array;
     DS_Size index;
};

ArrayIterator ArrayIterator_Create(Array array);

#endif