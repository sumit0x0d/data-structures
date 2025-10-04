
#include <array.h>

struct ArrayIterator {
     Array array;
     DS_Size index;
};

ArrayIterator ArrayIterator_Create(Array array);